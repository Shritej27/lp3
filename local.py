
# Gradient Descent Algorithm

# Define the function
def function(x):
    return (x + 3) ** 2

# Define the derivative
def derivative(x):
    return 2 * (x + 3)

# Initial value
x = 2

# Learning rate
learning_rate = 0.1

# Number of iterations
iterations = 50

# Gradient Descent
for i in range(iterations):
    x = x - learning_rate * derivative(x)

# Display result
print("Local Minimum point (x):", round(x, 4))
print("Minimum value (y):", round(function(x), 4))
