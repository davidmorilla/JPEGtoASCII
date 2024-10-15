# JPEG to ASCII Art Converter
This C program converts JPEG images to ASCII art using brightness values of pixels mapped to ASCII characters. It utilizes the libjpeg library for decoding and outputs the ASCII representation in the console. 

## Key Features:
- **JPEG Handling**: Utilizes the **libjpeg** library for decoding JPEG files.
- **Brightness Calculation**: Computes pixel brightness using the formula:
  
  **brightness = ((0.299 * R + 0.587 * G + 0.114 * B) * 91) / 255**

  where `R`, `G`, and `B` are the pixel color components. Note that it is multiplied by 91 in order to scale from 1 - 91 (the number of ASCII characters we are using for the mapping)
- **Character Mapping**: Maps calculated brightness levels to a predefined set of ASCII characters to create a visual representation of the image.
- **Input Validation**: Checks that the provided filename has a `.jpg` extension before processing.

## Usage:
Compile the program and run it from the command line by providing the JPEG file name as an argument:
`./ascii_art input.jpg`
This will print the output in the console.
If you´d rather save the output in a file, you can run this command instead:
`./ascii_art input.jpg > output.txt`


