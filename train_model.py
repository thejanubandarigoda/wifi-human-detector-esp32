import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score
import pickle
import os

# 1. Load the CSV File
csv_file = 'wifi_csi_dataset.csv'

if not os.path.exists(csv_file):
    print(f"Error: Cannot find '{csv_file}'. Check if the file is in the project folder.")
    exit()

print("Loading the dataset...")
df = pd.read_csv(csv_file)

# 2. Separate Features (RSSI values) and Target (Label)
X = df.drop('Label', axis=1) # RSSI columns
y = df['Label']              # Output Label (Empty_Room, Human_Walking, etc.)

# 3. Split the data into 80% for training and 20% for testing
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 4. Train the Model (Random Forest)
print(f"Training the AI Model using {len(df)} data rows...")
model = RandomForestClassifier(n_estimators=100, random_state=42)
model.fit(X_train, y_train)

# 5. Check the accuracy of the model
predictions = model.predict(X_test)
accuracy = accuracy_score(y_test, predictions)

print("\n" + "="*40)
print(f"✅ Model Training complete!")
print(f"🎯 Accuracy: {accuracy * 100:.2f}%")
print("="*40 + "\n")

# 6. Save the trained model for future use
with open('wifi_model.pkl', 'wb') as f:
    pickle.dump(model, f)
print("Your AI Model has been successfully saved as 'wifi_model.pkl'.")