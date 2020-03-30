# ProveSheldonConjecture
## This is a fun project using [My Makefile templates](https://github.com/johnzchgrd/Template/tree/master/%E9%93%BE%E6%8E%A5%E5%8A%A8%E6%80%81%E5%BA%93) to prove Sheldon Conjecture using Violent Enumeration with limit. 
And of course using Multi-threads (make sure you're using **posix** thread mode). See the [original single file](https://github.com/johnzchgrd/C-language-designing/blob/master/Sheldon%20conjuncture.c). More details in comments of [main file](./src/main.c).
## About the Outputs
In ```catme/``` is a simple program used to concatenate tmp files to ```Pn.tab``` (aka Prime Table). Since the generation of Prime Table is also Multi-threaded, this will create a temperary dir ```tmp/``` to store partial Prime Tables). This program also create an outputfile defined in the [main header](./include/local/sheldon.h) called ```OUTFILE``` to keep a pretty simple record of the run.
## About Threading
Threading is something new to me, and it's not used efficiently in this little project. The project uses posix mode and I used to believe GCC for Win32 can't use pthread😂.
## About Maintenance & Future Plans
This is my first __Starred__ project🙌! Aha, Milestone!

I would prefer to leave it as a project of my learning reminder of threading & Makefile scripting times (summer of 2019 at my grandparents' home), rather than make it perfect in every detail.