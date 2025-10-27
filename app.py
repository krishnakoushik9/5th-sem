import streamlit as st
import pickle
import string
from nltk.corpus import stopwords
import nltk
from nltk.stem.porter import PorterStemmer

# Initialize Porter Stemmer
ps = PorterStemmer()

# --- Text Preprocessing Function ---
# This function should be identical to the one you used for training
def transform_text(text):
    """
    Performs preprocessing on the input text:
    1. Lowercase
    2. Tokenize
    3. Remove special characters
    4. Remove stop words and punctuation
    5. Stemming
    """
    text = text.lower()
    text = nltk.word_tokenize(text)

    # Remove special characters
    y = [i for i in text if i.isalnum()]

    # Remove stop words and punctuation
    text = [i for i in y if i not in stopwords.words('english') and i not in string.punctuation]

    # Apply stemming
    y = [ps.stem(i) for i in text]

    return " ".join(y)


# --- Load Saved Files ---
try:
    # It's important to load both the vectorizer and the model
    tfidf = pickle.load(open('vectorizer.pkl', 'rb'))
    model = pickle.load(open('model.pkl', 'rb'))
except FileNotFoundError:
    st.error("Model or vectorizer file not found. Please make sure 'vectorizer.pkl' and 'model.pkl' are in the same directory.")
    st.stop()
except Exception as e:
    st.error(f"An error occurred while loading the files: {e}")
    st.stop()


# --- Streamlit Interface ---

st.set_page_config(
    page_title="Spam Classifier",
    page_icon="📧",
    layout="centered"
)

st.title("Email/SMS Spam Classifier")
st.markdown("Enter a message below to check if it's spam or not.")

# Text area for user input
input_sms = st.text_area("Enter the message")

# Prediction button
if st.button('Predict'):
    if not input_sms.strip():
        st.warning("Please enter a message to classify.")
    else:
        with st.spinner("Analyzing..."):
            # 1. Preprocess the input text
            transformed_sms = transform_text(input_sms)

            # 2. Vectorize the preprocessed text
            vector_input = tfidf.transform([transformed_sms])

            # 3. Predict using the loaded model
            result = model.predict(vector_input)[0]

            # 4. Display the result
            if result == 1:
                st.error("This message is likely Spam.")
            else:
                st.success("This message is Not Spam (Ham).")

st.markdown("---")
st.markdown("Built with Streamlit for your Naive Bayes model.")

