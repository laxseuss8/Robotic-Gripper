from tkinter import *
from PIL import ImageTk, Image
import cv2
import joblib
import tkinter as tk

# Define Window
ICap = tk.Tk()
ICap.title("ICap")
ICap.geometry("800x600")  # Larger main window size
ICap.configure(bg="white")

# Load the machine learning model
classifier = joblib.load('MixedVeggies.pkl')

# Create label for the webcam feed
frame2 = Label(ICap)
frame2.pack(pady=20)

# Create a Text widget for dynamic content below the webcam video using place
text_box = Text(ICap, height=5, width=60, font=("Helvetica", 12))
text_box.place(relx=0.5, rely=0.7, anchor="center")  # Adjust the placement as needed

# Open the webcam
cap = cv2.VideoCapture(0)

# Function to update GUI with webcam feed and dynamic text
def update_gui():
    try:
        # Read frame from webcam
        ret, frame = cap.read()

        # Convert the frame to RGB format
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        # Convert the frame to a PIL Image
        img = Image.fromarray(frame_rgb)

        # Resize the image to fit the smaller webcam window
        img = img.resize((400, 300))  # Adjust the size according to your preference
        img = ImageTk.PhotoImage(img)

        # Update the label with the webcam feed
        frame2.configure(image=img)
        frame2.image = img

        # Use the webcam frame as input to the machine learning model
        # Implement your machine learning logic here
        # For demonstration, assuming your classifier returns a label
        # Replace this with your actual machine learning logic
        detected_label = "Carrot"  # Example label, replace with your logic

        # Update the Text widget with dynamic content based on detection
        dynamic_text = f"Detected: {detected_label}"
        text_box.delete(1.0, END)  # Clear existing content
        text_box.insert(INSERT, dynamic_text)

        # Schedule the update after 100 milliseconds (0.1 second)
        ICap.after(100, update_gui)

    except KeyboardInterrupt:
        print("Program terminated by user")
        ICap.destroy()
    except Exception as e:
        print(f"Error: {e}")

# Call the update_gui function to start the webcam feed
update_gui()

# Center and place the webcam window a bit lower
frame2.place(relx=0.5, rely=0.3, anchor="center")

# Rest of your code (without the update_gui call)
ICap.mainloop()

# Release the webcam
cap.release()
