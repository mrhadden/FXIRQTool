# FXIRQTool

## Tool to visualize the Foenix IRQs
### Warning: The code is very beta and dripping wet, so changes daily based on understanding and hardware changes.

### Prerequisites:
* WDC development tools installed on your (Windows) computer. 
	http://westerndesigncenter.com/wdc/tools.cfm
* srec_cat.exe
	http://sourceforge.net/projects/srecord/files/srecord-win32/1.64/srecord-1.63-win32.zip 
* Java 1.8 - Needed to upload the code.  The C256 IDE won't load the image at the time of this writing.

* ONE TIME SETUP: Update the cmake.bat with the locations for your dev environment.

**You will need to attach the USB cable between the development computer to the C256**


### To make the project:
*From the source directory type: cmake*

### To make the project and push the code to the C256
*From the source directory type: cmake -t (t = transfer)*

### To NOT make the project and push the code to the C256
*From the source directory type: cmake -n -t (t = transfer/-n no build)*