
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans, AgglomerativeClustering
from scipy.cluster.hierarchy import dendrogram, linkage

# Load dataset
df = pd.read_csv("sales_data_sample.csv", encoding="ISO-8859-1")

print("First 5 rows:")
print(df.head())

# Select numerical columns
X = df[["QUANTITYORDERED", "SALES"]].dropna()

# Standardize data
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# Elbow Method
wcss = []

for k in range(1, 11):
    model = KMeans(n_clusters=k, random_state=42, n_init=10)
    model.fit(X_scaled)
    wcss.append(model.inertia_)

plt.plot(range(1, 11), wcss, marker="o")
plt.title("Elbow Method")
plt.xlabel("Number of Clusters")
plt.ylabel("WCSS")
plt.grid()
plt.show()

# Apply K-Means
k = 3

kmeans = KMeans(n_clusters=k, random_state=42, n_init=10)
df.loc[X.index, "KMeans_Cluster"] = kmeans.fit_predict(X_scaled)

print("\nK-Means Cluster Counts:")
print(df["KMeans_Cluster"].value_counts())

# K-Means plot
plt.scatter(X["QUANTITYORDERED"], X["SALES"],
            c=df.loc[X.index, "KMeans_Cluster"], cmap="viridis")
plt.title("K-Means Clustering")
plt.xlabel("Quantity Ordered")
plt.ylabel("Sales")
plt.show()

# Hierarchical Clustering
hc = AgglomerativeClustering(n_clusters=k)
df.loc[X.index, "Hierarchical_Cluster"] = hc.fit_predict(X_scaled)

print("\nHierarchical Cluster Counts:")
print(df["Hierarchical_Cluster"].value_counts())

# Hierarchical plot
plt.scatter(X["QUANTITYORDERED"], X["SALES"],
            c=df.loc[X.index, "Hierarchical_Cluster"], cmap="rainbow")
plt.title("Hierarchical Clustering")
plt.xlabel("Quantity Ordered")
plt.ylabel("Sales")
plt.show()

# Dendrogram (first 100 records)
Z = linkage(X_scaled[:100], method="ward")

plt.figure(figsize=(10, 5))
dendrogram(Z)
plt.title("Hierarchical Clustering Dendrogram")
plt.xlabel("Data Points")
plt.ylabel("Distance")
plt.show()

print("\nClustering completed successfully!")
