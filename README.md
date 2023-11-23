# libzcmdsh

## Overview

A GPL library for GNU Zebra/Quagga/FRR-like command-line shell.
It comes with the "opensh": It is provided as the first example application.
The "opensh" is a Cisco-like shell for "open"-ing files and directories
in MacOS. It especially shows a powerful ability when the name of the
file or directory is in the multi-byte language, e.g.,
the Jananese UTF-8 filename.

'?' provides a list of command candidates.
When in the <FILENAME> command node, '?' provides a list of
file candidates. 'TAB' will complete the command argument
as long as it is common among the candidates.

If you type '>' in the <FILENAME> command node, the shell enters
the ''file select mode'', where vi or emacs cursor move is accepted.
If you 'enter' in the file select mode, the candidate the cursor was on
is expanded in the command line.
'q' in the file select mode cancels the file select mode.

```
[/Users/yasu/devel]> '?'
  cd               change current working directory.
  exit             exit
  pwd              print current working directory.
  quit             quit
  ls               list files in the directory.
  logout           logout
  open             open.
[/Users/yasu/devel]> open '?'
  <FILENAME>       filename
  path:  dir: . filename: 
  maxlen: 27 ncol: 2

  simrouting/                  libzcmdsh/                   
  テストディレクトリ/ 
[/Users/yasu/devel]> open '>'
shell_input: inputch: 62/076/0x3e '>'
key_func: 0x104e3c190, key_func[62]: 0x104e369d4
[/Users/yasu/devel]> open debug...
  path:  dir: . filename: 

  path:  dir: . filename: 
  maxlen: 27 ncol: 2 nentry: 3 index: 0

  simrouting/                  libzcmdsh/                   
  テストディレクトリ/ 
shell_input: inputch: 10/012/0xa CONTROL('J')
key_func: 0x104e3d3a8, key_func[10]: 0x104e36de0
[/Users/yasu/devel]> open テストディレクトリ/'?'
shell_input: inputch: 63/077/0x3f '?'
key_func: 0x104e3c190, key_func[63]: 0x104e35a34
[/Users/yasu/devel]> open テストディレクトリ/
  <FILENAME>       filename
  path: テストディレクトリ/ dir: テストディレクトリ filename: 
  maxlen: 56 ncol: 1

  ランダム 空白入り日本語ファイル名.pdf  

[/Users/yasu/devel]> open テストディレクトリ/'>'
shell_input: inputch: 62/076/0x3e '>'
key_func: 0x104e3c190, key_func[62]: 0x104e369d4
[/Users/yasu/devel]> open テストディレクトリ/debug...
  path: テストディレクトリ dir: テストディレクトリ filename: 

  path: テストディレクトリ dir: テストディレクトリ filename: 
  maxlen: 56 ncol: 1 nentry: 1 index: 0

  ランダム 空白入り日本語ファイル名.pdf


shell_input: inputch: 10/012/0xa CONTROL('J')
key_func: 0x104e3d3a8, key_func[10]: 0x104e36de0
[/Users/yasu/devel]> open テストディレクトリ/ランダム 空白入り日本語ファイル名.pdf
shell_input: inputch: 10/012/0xa CONTROL('J')
key_func: 0x104e3c190, key_func[10]: 0x104e35820
[/Users/yasu/devel]> open テストディレクトリ/ランダム 空白入り日本語ファイル名.pdf
[/Users/yasu/devel]> 
```

