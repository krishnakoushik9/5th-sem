# Naive Bayes Text Classification Example
# Author: ChatGPT

from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.metrics import accuracy_score, classification_report

# 1. Sample data
texts = [
    "I love this movie, it’s amazing!",
    "What a terrible film, I hated it.",
    "Absolutely fantastic experience.",
    "Worst movie I have ever seen.",
    "I really enjoyed the storyline.",
    "The acting was awful and boring.",
    "Great direction and awesome plot!",
    "Not good, very disappointing.",
]

labels = [
    "positive",
    "negative",
    "positive",
    "negative",
    "positive",
    "negative",
    "positive",
    "negative",
]

# 2. Split into train and test sets
X_train, X_test, y_train, y_test = train_test_split(texts, labels, test_size=0.25, random_state=42)

# 3. Convert text to numerical feature vectors
vectorizer = CountVectorizer()
X_train_counts = vectorizer.fit_transform(X_train)
X_test_counts = vectorizer.transform(X_test)

# 4. Train Naive Bayes classifier
model = MultinomialNB()
model.fit(X_train_counts, y_train)

# 5. Make predictions
y_pred = model.predict(X_test_counts)

# 6. Evaluate performance
print("Accuracy:", accuracy_score(y_test, y_pred))
print("\nClassification Report:\n", classification_report(y_test, y_pred))

# 7. Test with new examples
new_texts = [
    "I loved the movie, it was so good!",
    "This was a waste of time, very bad."
]
new_counts = vectorizer.transform(new_texts)
predictions = model.predict(new_counts)

for text, pred in zip(new_texts, predictions):
    print(f"Text: {text} → Prediction: {pred}")