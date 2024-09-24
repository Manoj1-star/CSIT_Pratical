print("Name : Manoj KC")
print("Level : Bsc. Csit(4th sem) ")
print("Section : B")



from collections import defaultdict
import numpy as np

class NaiveBayes:
    def __init__(self):
        self.class_prob = {}
        self.feature_prob = defaultdict(lambda: defaultdict(lambda: defaultdict(float)))
        self.classes = []

    def fit(self, X, y):
        # Calculate class probabilities
        class_counts = defaultdict(int)
        feature_counts = defaultdict(lambda: defaultdict(lambda: defaultdict(int)))
        total_count = len(y)
        
        for label in y:
            class_counts[label] += 1
        
        self.classes = list(class_counts.keys())
        self.class_prob = {cls: count / total_count for cls, count in class_counts.items()}
        
        # Calculate feature probabilities
        for features, label in zip(X, y):
            for i, feature in enumerate(features):
                feature_counts[label][i][feature] += 1
        
        for cls in self.classes:
            for i in feature_counts[cls]:
                total_features = sum(feature_counts[cls][i].values())
                for feature in feature_counts[cls][i]:
                    self.feature_prob[cls][i][feature] = feature_counts[cls][i][feature] / total_features

    def predict(self, X):
        predictions = []
        for features in X:
            class_probabilities = {}
            for cls in self.classes:
                prob = self.class_prob[cls]
                for i, feature in enumerate(features):
                    prob *= self.feature_prob[cls][i].get(feature, 1e-6)  # Smoothing for unseen features
                class_probabilities[cls] = prob
            
            # Predict the class with the highest probability
            predicted_class = max(class_probabilities, key=class_probabilities.get)
            predictions.append(predicted_class)
        
        return predictions

# Example usage
if __name__ == "__main__":
    # Sample dataset
    X_train = [['sunny', 'hot', 'high', 'false'],
               ['sunny', 'hot', 'high', 'true'],
               ['overcast', 'hot', 'high', 'false'],
               ['rainy', 'mild', 'high', 'false'],
               ['rainy', 'cool', 'normal', 'false'],
               ['rainy', 'cool', 'normal', 'true'],
               ['overcast', 'cool', 'normal', 'true'],
               ['sunny', 'mild', 'high', 'false'],
               ['sunny', 'cool', 'normal', 'false'],
               ['rainy', 'mild', 'normal', 'true'],
               ['sunny', 'mild', 'normal', 'true'],
               ['overcast', 'mild', 'high', 'true'],
               ['overcast', 'hot', 'normal', 'false'],
               ['rainy', 'mild', 'high', 'false']]
    
    y_train = ['no', 'no', 'yes', 'yes', 'yes', 'no', 'yes', 'no', 'yes', 'yes', 'yes', 'yes', 'no', 'no']
    
    # Create and train the model
    model = NaiveBayes()
    model.fit(X_train, y_train)
    
    # Predict new data
    X_test = [['sunny', 'cool', 'high', 'true'],
              ['rainy', 'mild', 'normal', 'false']]
    
    predictions = model.predict(X_test)
    print("Predictions:", predictions)
