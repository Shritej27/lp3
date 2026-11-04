# Bank Customer Churn Prediction using ANN

import pandas as pd
import numpy as np

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score, confusion_matrix

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout , Input
from tensorflow.keras.callbacks import EarlyStopping

# Step 1: Read the dataset
df = pd.read_csv("Churn_Modelling.csv")

print("Dataset:")
print(df.head())
print("Dataset shape:", df.shape)

# Step 2: Separate features and target
# Remove unnecessary identification columns
X = df.drop(
    columns=["RowNumber", "CustomerId", "Surname", "Exited"]
)
y = df["Exited"]

# Convert categorical columns into numeric columns
X = pd.get_dummies(
    X, columns=["Geography", "Gender"], dtype=int
)

print("\nFeatures shape:", X.shape)
print("Target shape:", y.shape)

# Split into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)

# Step 3: Normalize the data
scaler = StandardScaler()

X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

print("\nTraining samples:", X_train.shape[0])
print("Testing samples:", X_test.shape[0])

# Step 4A: Build the basic ANN model
model1 = Sequential([
    Input(shape=(X_train.shape[1],)),
    Dense(16, activation="relu"),
    Dense(8, activation="relu"),
    Dense(1, activation="sigmoid")
])

model1.compile(
    optimizer="adam",
    loss="binary_crossentropy",
    metrics=["accuracy"]
)

model1.fit(
    X_train, y_train,
    epochs=20,
    batch_size=32,
    verbose=0
)

# Evaluate the basic model
y_prob1 = model1.predict(X_test, verbose=0)
y_pred1 = (y_prob1 >= 0.5).astype(int).ravel()

accuracy1 = accuracy_score(y_test, y_pred1)

print("\nBasic ANN Accuracy:", round(accuracy1 * 100, 2), "%")

# Step 4B: Improve the model
# Add more neurons, dropout and early stopping
model2 = Sequential([
    Input(shape=(X_train.shape[1],)),
    Dense(32, activation="relu"),
    Dropout(0.2),
    Dense(16, activation="relu"),
    Dropout(0.2),
    Dense(8, activation="relu"),
    Dense(1, activation="sigmoid")
])

model2.compile(
    optimizer="adam",
    loss="binary_crossentropy",
    metrics=["accuracy"]
)

early_stop = EarlyStopping(
    monitor="val_loss",
    patience=5,
    restore_best_weights=True
)

model2.fit(
    X_train, y_train,
    validation_split=0.2,
    epochs=50,
    batch_size=32,
    callbacks=[early_stop],
    verbose=0
)

# Step 5: Accuracy and confusion matrix
y_prob2 = model2.predict(X_test, verbose=0)
y_pred2 = (y_prob2 >= 0.5).astype(int).ravel()

accuracy2 = accuracy_score(y_test, y_pred2)
cm = confusion_matrix(y_test, y_pred2)

print("\nImproved ANN Accuracy:", round(accuracy2 * 100, 2), "%")
print("\nConfusion Matrix:")
print(cm)

print("\nModel Comparison:")
print("Basic ANN:", round(accuracy1 * 100, 2), "%")
print("Improved ANN:", round(accuracy2 * 100, 2), "%")
