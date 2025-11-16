import os
from deepface import DeepFace

def list_images(folder="."):
    """List image files from folder."""
    exts = (".jpg", ".jpeg", ".png", ".bmp")
    return [f for f in os.listdir(folder) if f.lower().endswith(exts)]

def detect_emotion(image_path):
    """Detect emotion using DeepFace (lightweight TensorFlow backend)."""
    try:
        result = DeepFace.analyze(img_path=image_path, actions=["emotion"], enforce_detection=True)
        dominant = result[0]["dominant_emotion"]
        print(f"\n✅ Detected Expression: {dominant.upper()}")
        print("📊 Emotion Scores:")
        for emotion, score in result[0]["emotion"].items():
            print(f"  {emotion:10s}: {score:.3f}")
    except Exception as e:
        print(f"⚠️  Error: {e}")

def main():
    folder = input("📂 Enter folder path (leave empty for current dir): ").strip() or "."
    if not os.path.isdir(folder):
        print("❌ Invalid folder.")
        return

    images = list_images(folder)
    if not images:
        print("⚠️  No image files found.")
        return

    print("\n🖼️ Available Images:")
    for i, name in enumerate(images, 1):
        print(f"{i}. {name}")
    
    try:
        choice = int(input("\n👉 Enter image number: "))
        if 1 <= choice <= len(images):
            path = os.path.join(folder, images[choice - 1])
            detect_emotion(path)
        else:
            print("❌ Invalid choice.")
    except ValueError:
        print("❌ Enter a valid number.")

if __name__ == "__main__":
    main()
"""Emotion Detection using DeepFace with TensorFlow backend."""
