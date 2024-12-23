# Image Processing Program for P2, P3, P5, and P6 Formats

## Overview
This program reads image files in P2, P3 (ASCII grayscale and RGB), and P5, P6 (binary grayscale and RGB) formats. It allows users to perform various operations such as rotation, cropping, equalization, histogram generation, and applying filters. The processed images can be saved in either text (ASCII) or binary formats.

## Data Structures
Two types of dynamically allocated structs are used:
1. **RGB Images**: For images with color.
2. **Grayscale Images**: For black-and-white images.

Each struct stores:
- The image type.
- Dimensions (width and height).
- Maximum pixel value.
- Pixel data.

---

## Functions

### **LOAD**
- Extracts the file name from the command.
- Reads the file to determine the image type, dimensions, and maximum pixel value.
- Allocates memory for the image.
- Opens the file in text or binary mode to read its contents:
  - Binary images are read byte-by-byte to extract pixel values.
- By default, the entire image is selected for processing.

---

### **SAVE**
- Extracts the destination file path from the command.
- Checks for the word `ascii` in the command:
  - If found, saves the image in text format.
  - Otherwise, saves the image in binary format.
- Adjusts the image type according to the save format.

---

### **SELECT**
- If the command contains `ALL`, selects the entire image.
- Otherwise:
  - Extracts four numbers representing the coordinates of the upper-left and lower-right corners of the selection.
  - Validates the coordinates:
    - Ensures exactly four numbers are provided.
    - Checks if the coordinates are within bounds.
  - Prints an error if validation fails.

---

### **ROTATE**
- Rotates the selected region or the entire image.
- Ensures that the selected region is square; otherwise, prints an error.
- Uses an auxiliary matrix to store the rotated image:
  - Each 90° rotation involves rearranging pixels using a formula.
- Updates the dimensions of the selected region if the entire image is rotated.

---

### **CROP**
- Crops the image to the currently selected region.
- Copies the selected pixels into an auxiliary matrix.
- Frees the original image memory.
- Points the image struct to the new cropped matrix.

---

### **APPLY**
- Applies the following filters to **RGB images** in the selected region:
  - `BLUR`
  - `SHARPEN`
  - `EDGE`
  - `GAUSSIAN BLUR`
- Leaves the edge pixels unchanged.
- Performs calculations in double precision:
  - Rounds values to integers before storing them.
  - Updates the original image using a temporary matrix.

---

### **EQUALIZE**
- Equalizes the pixel values of a **grayscale image**.
- Steps:
  1. Creates a frequency array to count occurrences of each pixel value.
  2. Applies the equalization formula to adjust pixel values across the image.

---

### **HISTOGRAM**
- Generates and prints a histogram of the image:
  - Creates a frequency array for pixel values.
  - Extracts the maximum number of stars and the number of bins from the command.
  - Divides the pixel range into bins.
  - Aggregates frequencies for each bin and prints a histogram to `STDOUT`.

---

## Notes
- **Error Handling**: All functions validate that an image is loaded before proceeding. If no image is loaded, an error is printed.
- **Memory Management**: All dynamic allocations ensure efficient memory usage, freeing unused memory when appropriate.