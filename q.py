import numpy as np
import pandas as pd
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import train_test_split
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, LSTM

# Step 1: Data Collection (example using a CSV file)
data = pd.read_csv('stock_data.csv')

# Step 2: Data Preprocessing
# Selecting the 'Close' column for simplicity
data = data[['Close']]
data = data.dropna()  # Drop missing values

# Normalize the data
scaler = MinMaxScaler(feature_range=(0, 1))
scaled_data = scaler.fit_transform(data)

# Create sequences of 60 days for prediction
def create_sequences(data, seq_length):
    X, y = [], []
    for i in range(seq_length, len(data)):
        X.append(data[i-seq_length:i, 0])
        y.append(data[i, 0])
    return np.array(X), np.array(y)

seq_length = 60
X, y = create_sequences(scaled_data, seq_length)

# Reshape X to fit LSTM layer's expected input
X = X.reshape(X.shape[0], X.shape[1], 1)

# Step 3: Splitting the Data
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Step 4: Building the ANN
model = Sequential()
model.add(LSTM(50, return_sequences=True, input_shape=(seq_length, 1)))
model.add(LSTM(50, return_sequences=False))
model.add(Dense(25))
model.add(Dense(1))

# Step 5: Compiling the Model
model.compile(optimizer='adam', loss='mean_squared_error')

# Step 6: Training the Model
model.fit(X_train, y_train, batch_size=32, epochs=50, validation_split=0.1)

# Step 7: Evaluating the Model
loss = model.evaluate(X_test, y_test)
print(f'Test Loss: {loss}')

# Step 8: Making Predictions
predictions = model.predict(X_test)
predictions = scaler.inverse_transform(predictions)

# Compare with the actual values
actual_prices = scaler.inverse_transform(y_test.reshape(-1, 1))

# Visualization
import matplotlib.pyplot as plt

plt.figure(figsize=(14, 5))
plt.plot(actual_prices, color='blue', label='Actual Stock Price')
plt.plot(predictions, color='red', label='Predicted Stock Price')
plt.title('Stock Price Prediction')
plt.xlabel('Time')
plt.ylabel('Stock Price')
plt.legend()
plt.show()
