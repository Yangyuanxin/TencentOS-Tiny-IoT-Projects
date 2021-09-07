## Generate CMSIS Pack for Release

This folder contains TencentOS Tiny software components (RTOS)

To build a complete CMSIS pack for installation the following additional tools are required:

 - **PACK.xsd**     (PDSC detector)

 - **PackChk.exe**     (Packing tool detector)
 - **7z.exe (7-Zip)** Version: 16.02 (File Archiver)

Using these tools, you can generate on a Windows PC:

 - **CMSIS Software Pack** using the batch file **gen_pack.bat** (located in ./TencentOS-tiny-softpack).



## Directory Structure

| Directory                                   | Content                                                      |
| :------------------------------------------ | :----------------------------------------------------------- |
| CMSIS/Core                                  | CMSIS-Core(M) related files (for release)                    |
| CMSIS/CoreValidation                        | Validation for Core(M) and Core(A) (NOT part of release)     |
| CMSIS/DAP                                   | CMSIS-DAP related files and examples                         |
| CMSIS/Driver                                | CMSIS-Driver API headers and template files                  |
| CMSIS/DSP                                   | CMSIS-DSP related files                                      |
| CMSIS/RTOS                                  | RTOS v1 related files (for Cortex-M)                         |
| CMSIS/RTOS2                                 | RTOS v2 related files (for Cortex-M & Armv8-M)               |
| CMSIS/Pack                                  | CMSIS-Pack examples and tutorials                            |
| CMSIS/DoxyGen                               | Source of the documentation                                  |
| CMSIS/Utilities                             | Utility programs                                             |
| CMSIS/RTOS/TencentOS_tiny/INC               | Store TencentOS_tiny to cmsis_os API header file             |
| CMSIS/RTOS/TencentOS_tiny/LIB               | Store TencentOS_tiny CPU architecture                        |
| CMSIS/RTOS/TencentOS_tiny/SRC               | Store TencentOS_tiny kernel，TOS_CONFIG，files related to compilation |
| CMSIS/RTOS/TencentOS_tiny/UserCodeTemplates | Store TencentOS_tiny User code templates                     |
| Docs                                        | Store project description documents                          |



