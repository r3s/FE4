** Note: This application is not to be used for your encryption purposes **


# FE 4 - File Encoder 4
-----------------------------------------------
In case you want to try it out before reading what I have to say: http://download.cnet.com/FE4/3000-2381_4-10851484.html

-----------------------------------------------

FE4 or File Encoder 4 is a Windows application written in C++ using the Win32 API that can be used to encrypt, shred, mass rename and search for files. It also has some other features like clearing temporary files and some other things I have forgotten.

#### History
FE4 or File Encoder 4 was one of my first full featured application with a real window based GUI and several functions. It is written in C++, the second programming language I learned in school after QBASIC(way back in 4th grade, 1999. There was nothing computer after 4th grade up until 11th grade). I wrote FE4 the second year I started learning C++(2007). Mind you, we had like 40 minutes of computer science class from Monday through Friday and only one or two days during the period were we allowed to use the computer lab. I can't remember the year I got a computer at home but I could only have had started programming in late 2005.

FE4 has had it's share of predecessors. The first 3 FE's were DOS based and had only commandline operations on a single file. Those have all resided in my school's computer lab and have never seen an outside computer.

FE4 was written probably in early 2007, but I am really not sure. The modified date on the source files show the month April 2007, which probably is true. It was created using the Borland C++ 5.02 (version number may be different but was definitely 5), utilizing the Win32 API. It was an opportunity for me to put to use the C++ I had learned in school. I ended up using only the basic functional programming ideas, and was not skillful enough to implement OOP. And after I don't know how long, FE4 was born.

#### Encryption.

My interest in encryption during that time was really evident in my projects. Every simple program I wrote in school were to encrypt messages or files. I was going on implementing my own encryption techniques, which I later realized was nothing but variations of ROT cipher. One of the projects I did for school was an early version of FE, which used the graphics.h library for the UI. I made simple widgets like buttons and tables for me to use in the program. I really wish I had the source so that I could see the spirit I once had in programming which seems to be lost. But that's a story for another day.

FE4 is using some weird XOR based encryption, but I really cannot remember how I went about it. The code for the encryption and decryption was separated in to a DLL file, whose source file I am unable to find. I do remember reading about cryptography at the time but have no idea if I have applied any of it in the application.

#### What is in the repo?

The repo contains the C++ source code for the main  window of the application, a header file, the resource id file, some IDE file, and a header for what looks like another DLL file used to for some file dialogs. Don't expect any comments in the source. I found the source code in the Sent folder of my mail, sent in 2008 to a friend. The content of the mail said:

` here is it, without bmps and dlls `

and a 7z file was attached. I am uploading everything in that archive to the repo.


#### I want to hear more!

Well, you got it! I happened to upload application to CNET's download.com website. This was done almost a year later in 2008, and had around 131 downloads! I even was able to get a review from an editor to make a proper installer for the application. I didn't know how to use the available free installer maker software at the time. I had to add a registry entry to support right-click context menu and I couldn't or the life of it figure out how to make that work. So what I did was to make the whole package a WinRAR self extracting archive and to run a small app I made myself to setup the registry keys. If you are curious, you can find the working FE4 at http://download.cnet.com/FE4/3000-2381_4-10851484.html

#### The END

That's it folks. It was nice to go and visit the past and remember how much I loved writing programs (even if they were shitty ones). I seem to have lost that feeling and that happiness one gets when you get to see your creation up and running. I might upload other programs I made during those time if I am able to recover files from my old IDE hard drive. Till then, cheerio.
