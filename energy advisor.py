"""Smart Hostel Energy Advisor - 15-row sample analysis.

Takes 15 consecutive months of one (synthetic) hostel block from the larger sample
and runs Linear Regression, Decision Tree, K-Means and PCA on them.
All values are made up for the assignment; they are not real meter readings.

Usage: python hostel_analysis_15rows.py [source_csv] [output_dir] [k_for_kmeans]
"""
import json
import os
import sys

import matplotlib
import numpy as np
import pandas as pd

matplotlib.use("Agg")
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn.decomposition import PCA
from sklearn.linear_model import LinearRegression
from sklearn.metrics import (mean_absolute_error, mean_squared_error,
                             r2_score, silhouette_score)
from sklearn.model_selection import (LeaveOneOut, cross_val_predict,
                                     train_test_split)
from sklearn.preprocessing import StandardScaler
from sklearn.tree import DecisionTreeRegressor

SRC = sys.argv[1] if len(sys.argv) > 1 else "/home/claude/work/out/hostel_sample_dataset.csv"
OUT = sys.argv[2] if len(sys.argv) > 2 else "/home/claude/work/out15"
K_OVERRIDE = int(sys.argv[3]) if len(sys.argv) > 3 else None
os.makedirs(OUT, exist_ok=True)
SEED = 42

# ----------------------------------------------------------------- 1. data
src = pd.read_csv(SRC)
df = (src[src.block == "D"].sort_values("month").head(15).reset_index(drop=True))
df = df[["month", "previous_kwh", "students", "occupied_rooms", "ac_units",
         "avg_temp", "season", "next_kwh"]]
df.to_csv(f"{OUT}/hostel_sample_dataset_15rows.csv", index=False)

FEATS = ["previous_kwh", "students", "occupied_rooms", "ac_units", "avg_temp"]
X, y = df[FEATS], df["next_kwh"]
res = {"n_rows": len(df), "months": df.month.tolist(),
       "season_counts": df.season.value_counts().to_dict(),
       "y_mean": y.mean(), "y_min": y.min(), "y_max": y.max(),
       "corr_students_rooms": float(df.students.corr(df.occupied_rooms)),
       "rows": df.to_dict(orient="records")}


def metrics(yt, yp):
    yt, yp = np.asarray(yt, float), np.asarray(yp, float)
    return dict(MAE=float(mean_absolute_error(yt, yp)),
                RMSE=float(np.sqrt(mean_squared_error(yt, yp))),
                R2=float(r2_score(yt, yp)))


# ---------------------------------------------------------- 2. split + LOO
Xtr, Xte, ytr, yte = train_test_split(X, y, test_size=.2, random_state=SEED)
res["n_train"], res["n_test"] = len(Xtr), len(Xte)
res["test_months"] = df.loc[Xte.index, "month"].tolist()
loo = LeaveOneOut()

# persistence reference: next month = this month
res["baseline_split"] = metrics(yte, Xte["previous_kwh"])
res["baseline_loo"] = metrics(y, X["previous_kwh"])

# ------------------------------------------------------ 3. linear regression
lr_tr = LinearRegression().fit(Xtr, ytr)
res["lr_split"] = metrics(yte, lr_tr.predict(Xte))
p_lr = cross_val_predict(LinearRegression(), X, y, cv=loo)
res["lr_loo"] = metrics(y, p_lr)
lr_all = LinearRegression().fit(X, y)
res["lr_intercept"] = float(lr_all.intercept_)
res["lr_coef"] = dict(zip(FEATS, map(float, lr_all.coef_)))
res["lr_train_r2"] = float(r2_score(y, lr_all.predict(X)))

# ----------------------------------------------------------- 4. decision tree
DEPTH = 2
dt_tr = DecisionTreeRegressor(max_depth=DEPTH, random_state=SEED).fit(Xtr, ytr)
res["dt_split"] = metrics(yte, dt_tr.predict(Xte))
p_dt = cross_val_predict(DecisionTreeRegressor(max_depth=DEPTH, random_state=SEED),
                         X, y, cv=loo)
res["dt_loo"] = metrics(y, p_dt)
dt = DecisionTreeRegressor(max_depth=DEPTH, random_state=SEED).fit(X, y)
res["dt_importance"] = dict(zip(FEATS, map(float, dt.feature_importances_)))
sweep = []
for d in [1, 2, 3, 4, None]:
    m_ = DecisionTreeRegressor(max_depth=d, random_state=SEED).fit(X, y)
    pl = cross_val_predict(DecisionTreeRegressor(max_depth=d, random_state=SEED), X, y, cv=loo)
    sweep.append(dict(depth="None" if d is None else d, leaves=int(m_.get_n_leaves()),
                      train_r2=float(r2_score(y, m_.predict(X))),
                      loo_r2=float(r2_score(y, pl)),
                      loo_mae=float(mean_absolute_error(y, pl))))
res["dt_sweep"] = sweep
T = dt.tree_
res["dt_nodes"] = [dict(node=i, leaf=bool(T.children_left[i] == -1),
                        feature=(FEATS[T.feature[i]] if T.children_left[i] != -1 else None),
                        threshold=float(T.threshold[i]), n=int(T.n_node_samples[i]),
                        value=float(T.value[i][0][0]),
                        left=int(T.children_left[i]), right=int(T.children_right[i]))
                   for i in range(T.node_count)]

# ------------------------------------------------------------- 5. k-means
Xs = StandardScaler().fit_transform(X)
km_tab = []
for k in range(2, 6):
    km_ = KMeans(n_clusters=k, n_init=10, random_state=SEED).fit(Xs)
    km_tab.append(dict(k=k, inertia=float(km_.inertia_),
                       silhouette=float(silhouette_score(Xs, km_.labels_))))
res["kmeans_table"] = km_tab
best_k = max(km_tab, key=lambda r: r["silhouette"])["k"]
K = K_OVERRIDE or best_k
res["k_best_silhouette"], res["k_used"] = best_k, K
km = KMeans(n_clusters=K, n_init=10, random_state=SEED).fit(Xs)
df["cluster"] = km.labels_
order = df.groupby("cluster")["next_kwh"].mean().sort_values().index.tolist()
df["cluster"] = df.cluster.map({old: new for new, old in enumerate(order)})
prof = df.groupby("cluster").agg(rows=("month", "size"), previous_kwh=("previous_kwh", "mean"),
                                 students=("students", "mean"),
                                 occupied_rooms=("occupied_rooms", "mean"),
                                 ac_units=("ac_units", "mean"), avg_temp=("avg_temp", "mean"),
                                 next_kwh=("next_kwh", "mean"))
res["clusters"] = prof.round(2).reset_index().to_dict(orient="records")
res["cluster_members"] = {int(c): g.month.tolist() for c, g in df.groupby("cluster")}
res["cluster_seasons"] = {int(c): g.season.value_counts().to_dict() for c, g in df.groupby("cluster")}
df.to_csv(f"{OUT}/hostel_sample_dataset_15rows_with_clusters.csv", index=False)

# ----------------------------------------------------------------- 6. PCA
pca = PCA(random_state=SEED).fit(Xs)
Z = pca.transform(Xs)
res["pca_var"] = pca.explained_variance_ratio_.tolist()
res["pca_loadings"] = {f: [float(pca.components_[0][i]), float(pca.components_[1][i])]
                       for i, f in enumerate(FEATS)}

# ---------------------------------------------------------------- 7. figures
C = ["#2a78d6", "#eb6834", "#1baf7a", "#eda100", "#e87ba4"]
INK, SEC, MUTED, GRID, BASE, SURF = "#0b0b0b", "#52514e", "#898781", "#e1e0d9", "#c3c2b7", "#fcfcfb"
plt.rcParams.update({
    "font.family": "sans-serif", "font.size": 9, "figure.facecolor": SURF,
    "axes.facecolor": SURF, "axes.edgecolor": BASE, "axes.labelcolor": SEC,
    "xtick.color": MUTED, "ytick.color": MUTED, "text.color": INK,
    "axes.spines.top": False, "axes.spines.right": False,
    "axes.grid": True, "grid.color": GRID, "grid.linewidth": .6,
    "axes.axisbelow": True, "axes.titlesize": 10, "axes.titleweight": "bold",
    "axes.titlecolor": INK, "axes.titlelocation": "left"})
MON = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"]
short = [f"{MON[int(m[5:]) - 1]} {m[2:4]}" for m in df.month]


def save(fig, name):
    fig.savefig(f"{OUT}/{name}.png", dpi=200, bbox_inches="tight", facecolor=SURF)
    plt.close(fig)


# fig 1: the 15 months (two measures -> two charts)
fig, ax = plt.subplots(2, 1, figsize=(6.5, 4.2), sharex=True, gridspec_kw={"height_ratios": [1.5, 1]})
x = np.arange(15)
ax[0].plot(x, df.previous_kwh, color=C[0], lw=2, marker="o", ms=5, markeredgecolor=SURF)
ax[0].set_title("Electricity used in each month (Block D)")
ax[0].set_ylabel("kWh")
ax[0].yaxis.set_major_formatter(matplotlib.ticker.FuncFormatter(lambda v, _: f"{v:,.0f}"))
ax[1].plot(x, df.avg_temp, color=C[1], lw=2, marker="o", ms=5, markeredgecolor=SURF)
ax[1].set_title("Average temperature")
ax[1].set_ylabel("°C")
ax[1].set_xticks(x)
ax[1].set_xticklabels(short, rotation=45, ha="right")
fig.tight_layout()
save(fig, "fig1_overview")

# fig 2: actual vs predicted (leave-one-out) for both models
fig, ax = plt.subplots(1, 2, figsize=(6.5, 3.3), sharex=True, sharey=True)
lo, hi = float(y.min()) * .95, float(y.max()) * 1.12
for a, p, nm, col, key in [(ax[0], p_lr, "Linear Regression", C[0], "lr_loo"),
                           (ax[1], p_dt, f"Decision Tree (depth {DEPTH})", C[1], "dt_loo")]:
    a.plot([lo, hi], [lo, hi], ls="--", lw=1, color=MUTED)
    a.scatter(y, p, s=30, color=col, edgecolor=SURF, linewidth=.8, zorder=3)
    r = res[key]
    a.set_title(nm)
    a.text(.04, .93, f"R² = {r['R2']:.3f}\nMAE = {r['MAE']:,.0f} kWh", transform=a.transAxes,
           va="top", color=SEC, fontsize=8.5)
    a.set_xlabel("Actual next-month use (kWh)")
    a.set_xlim(lo, hi)
    a.set_ylim(lo, hi)
ax[0].set_ylabel("Predicted (kWh)")
fig.tight_layout()
save(fig, "fig2_actual_vs_pred")

# fig 3: decision tree (custom drawing)
fig, a = plt.subplots(figsize=(6.5, 3.0))
a.axis("off")
a.grid(False)
NICE = {"previous_kwh": "prev kWh", "students": "students", "occupied_rooms": "rooms",
        "ac_units": "AC units", "avg_temp": "temp °C"}
leaf_counter = [0]
pos = {}


def layout(n, depth):
    if T.children_left[n] == -1:
        pos[n] = (leaf_counter[0], -depth)
        leaf_counter[0] += 1
    else:
        layout(T.children_left[n], depth + 1)
        layout(T.children_right[n], depth + 1)
        pos[n] = ((pos[T.children_left[n]][0] + pos[T.children_right[n]][0]) / 2, -depth)


layout(0, 0)
for n, (x_, y_) in pos.items():
    if T.children_left[n] != -1:
        for ch, lab in [(T.children_left[n], "yes"), (T.children_right[n], "no")]:
            cx, cy = pos[ch]
            a.plot([x_, cx], [y_ - .13, cy + .13], color=BASE, lw=1.2, zorder=1)
            a.text((x_ + cx) / 2, (y_ + cy) / 2 + .02, lab, fontsize=8, color=MUTED,
                   ha="center", va="center", backgroundcolor=SURF, zorder=2)
for n, (x_, y_) in pos.items():
    leaf = T.children_left[n] == -1
    if leaf:
        txt = f"n = {int(T.n_node_samples[n])}\n{T.value[n][0][0]:,.0f} kWh"
    else:
        txt = f"{NICE[FEATS[T.feature[n]]]} ≤ {T.threshold[n]:,.1f}?\nn = {int(T.n_node_samples[n])}"
    a.text(x_, y_, txt, ha="center", va="center", fontsize=8.5, color=INK, zorder=3,
           bbox=dict(boxstyle="round,pad=0.4", fc=SURF if not leaf else "#e8f0fb", ec=C[0], lw=1))
a.set_xlim(-.7, leaf_counter[0] - .3)
a.set_ylim(-2.45, .45)
save(fig, "fig3_tree")

# fig 4: elbow + silhouette
ks = [r["k"] for r in km_tab]
fig, ax = plt.subplots(1, 2, figsize=(6.5, 2.9))
ax[0].plot(ks, [r["inertia"] for r in km_tab], color=C[0], lw=2, marker="o", ms=5, markeredgecolor=SURF)
ax[0].set_title("Elbow curve")
ax[0].set_ylabel("Inertia")
ax[1].plot(ks, [r["silhouette"] for r in km_tab], color=C[1], lw=2, marker="o", ms=5, markeredgecolor=SURF)
ax[1].set_title("Silhouette score")
for a in ax:
    a.set_xlabel("Number of clusters (k)")
    a.set_xticks(ks)
    a.axvline(K, color=MUTED, lw=1, ls=":")
    lo_, hi_ = a.get_ylim()
    a.text(K + .05, hi_ - (hi_ - lo_) * .06, f"k = {K} used", color=SEC, fontsize=8, va="top")
fig.tight_layout()
save(fig, "fig4_kmeans_selection")

# fig 5: PCA scatter (rows labelled by month) + scree
mk = ["o", "s", "^", "D", "v"]
fig, ax = plt.subplots(1, 2, figsize=(6.5, 3.5), gridspec_kw={"width_ratios": [1.7, 1]})
for c in range(K):
    s = df.cluster.values == c
    ax[0].scatter(Z[s, 0], Z[s, 1], s=34, color=C[c], marker=mk[c], edgecolor=SURF,
                  linewidth=.6, label=f"Cluster {c}", zorder=3)
for i, lab in enumerate(short):
    ax[0].annotate(lab, (Z[i, 0], Z[i, 1]), textcoords="offset points", xytext=(4, 4),
                   fontsize=6.5, color=SEC)
ax[0].set_xlabel(f"PC1 ({res['pca_var'][0] * 100:.1f}%)")
ax[0].set_ylabel(f"PC2 ({res['pca_var'][1] * 100:.1f}%)")
ax[0].set_title("First two principal components")
ax[0].legend(frameon=False, fontsize=8, loc="best")
ax[1].bar(range(1, len(FEATS) + 1), np.array(res["pca_var"]) * 100, color=C[0], width=.55)
ax[1].set_xticks(range(1, len(FEATS) + 1))
ax[1].set_xlabel("Component")
ax[1].set_ylabel("Variance explained (%)")
ax[1].set_title("Scree plot")
fig.tight_layout()
save(fig, "fig5_pca")

# --------------------------------------------------------------- 8. dump
json.dump(res, open(f"{OUT}/results15.json", "w"), indent=2, default=float)

pd.set_option("display.width", 200)
print(df.drop(columns="cluster").to_string(index=False))
print("train/test", res["n_train"], res["n_test"], "test months", res["test_months"])
print("baseline split", {k: round(v, 3) for k, v in res["baseline_split"].items()})
print("baseline loo  ", {k: round(v, 3) for k, v in res["baseline_loo"].items()})
print("LR split", {k: round(v, 3) for k, v in res["lr_split"].items()})
print("LR loo  ", {k: round(v, 3) for k, v in res["lr_loo"].items()}, "train R2", round(res["lr_train_r2"], 3))
print("LR coef", {k: round(v, 2) for k, v in res["lr_coef"].items()}, "int", round(res["lr_intercept"], 1))
print("DT split", {k: round(v, 3) for k, v in res["dt_split"].items()})
print("DT loo  ", {k: round(v, 3) for k, v in res["dt_loo"].items()})
print("DT imp", {k: round(v, 3) for k, v in res["dt_importance"].items()})
print(pd.DataFrame(sweep).round(3).to_string(index=False))
print(pd.DataFrame(km_tab).round(4).to_string(index=False), "best k", best_k, "used", K)
print(prof.round(1).to_string())
print(res["cluster_members"])
print("PCA var", [round(v, 4) for v in res["pca_var"]])
print("loadings", {k: [round(a, 3) for a in v] for k, v in res["pca_loadings"].items()})
print("corr students~rooms", round(res["corr_students_rooms"], 3))
