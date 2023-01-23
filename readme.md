# RobinLe Tools
This is a collection of small Windows tools I created.



## FilenameFriendlyClipboard
Changes the clipboard (if the current content is text compatible) to be usable as a filename under Microsoft Windows.

This is achieved by substituting disallowed characters by similar looking characters.

### Conversion table
| Original            | Replacement              |
|---------------------|--------------------------|
| ```/```             |  ```／``` (```U+FF0F```) |
| ```\```             |  ```＼``` (```U+FF3C```) |
| ```:```             |  ```：``` (```U+FF1A```) |
| ```*```             |  ```＊``` (```U+FF0A```) |
| ```?```             |  ```？``` (```U+FF1F```) |
| ```"```             |  ```''``` (2x ```'```)   |
| ```<```             |  ```＜``` (```U+FF1C```) |
| ```>```             |  ```＞``` (```U+FF1E```) |
| <code>&#124;</code> |  ```｜``` (```U+FF5C```) |


## MoorhuhnTools
Multiple tools for working with binary files from multiple of the Moorhuhn (Crazy Chicken) games.

### MH3Extract
Extract data from a Moorhuhn 3 ```moorhuhn3.dat```.

### MHJnRExtract
Extract data from a Moorhuhn Schatzjäger (AKA Moorhuhn Jump'n'Run) ```datafile.dat```.


## StartupDelete
Clears one directory based on the call parameters.
The idea is to have a directory that gets deleted on every computer startup - you can achieve this by creating a link to the programm in your computer's autostart folder (*%AppData%\Microsoft\Windows\Start Menu\Programs\Startup*).

### Syntax
```
StartupDelete.exe <Directory>
```
So a call could look like this:
```
StartupDelete.exe C:\TEMP
```
