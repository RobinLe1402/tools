> [!IMPORTANT]
> On 2024-10-13, I deprecated this repository by creating separate repos
> for the applications previously created here:
> [FilenameFriendlyClipboard](https://rle.sh/git-repo/FilenameFriendlyClipboard),
> [MoorhuhnTools](https://rle.sh/git-repo/MoorhuhnTools),
> [ClearDir](https://rle.sh/git-repo/ClearDir) (previously StartupDelete).

# RobinLe Tools
This is a collection of small Windows tools I created.

Compatible with Windows XP.



## FilenameFriendlyClipboard
Changes the clipboard (if the current content is text compatible) to be usable as a filename under Microsoft Windows.

This is achieved by substituting disallowed characters with similar looking characters.

### Conversion table
| Original            | Replacement      |
|---------------------|------------------|
| `/`                 |  `／` (`U+FF0F`) |
| `\`                 |  `＼` (`U+FF3C`) |
| `:`                 |  `：` (`U+FF1A`) |
| `*`                 |  `＊` (`U+FF0A`) |
| `?`                 |  `？` (`U+FF1F`) |
| `"`                 |  `''` (2x `'`)   |
| `<`                 |  `＜` (`U+FF1C`) |
| `>`                 |  `＞` (`U+FF1E`) |
| <code>&#124;</code> |  `｜` (`U+FF5C`) |


## MoorhuhnTools
Multiple tools for working with binary files from multiple of the Moorhuhn (Crazy Chicken) games.

### MH3Extract
Extract data from Moorhuhn 3's `moorhuhn3.dat`.

### MHJnRExtract
Extract data from Moorhuhn Schatzjäger's (AKA Moorhuhn Jump'n'Run) `datafile.dat`.


## StartupDelete
Clears one directory based on the call parameters.
The idea is to have a directory that gets deleted on every startup - you can achieve this by placing 
a link to the executable in Windows' autostart folder (`%AppData%\Microsoft\Windows\Start Menu\Programs\Startup`).

### Syntax
```
StartupDelete.exe <Directory>
```
So a call could look like this:
```
StartupDelete.exe C:\TEMP
```
