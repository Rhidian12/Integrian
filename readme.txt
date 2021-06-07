https://github.com/Rhidian12/Integrian

The menu can be traversed with the arrow keys and selected with ENTER.
Player one plays with the keys EDAQ and player two with the buttons XABY on the controller.

NOTE:
FOR SOME REASON, BATCH BUILDING DOES NOT COMPILE Release x64 and Release x86
CLEAN AND BUILD THESE SEPERATELY FOR SUCCESSFULL COMPILATION

There are many good design choices (in my humble opinion), but there are many bad design choices as well:

* Good Ones:

- For one, I'm very happy with how my InputManager and Audio System turned out. I had to fix some SDL related shenanigans last minute in the InputManager, but I'm very happy with it.

- Use of templates. I am pretty sure when I say that not many in the second year are able to do what I can with templates, which is something I'm very proud of. Most
of these changes don't save a lot of time, but every second counts and some functions make my life easier, such as an Erase_If for maps, which is something you normally can't do.

- The EventQueue works pretty well. The only change I'd add now is 2 seperate EventQueues: One for the Engine and one for the User.

- Wrappers. Most things have a nice wrapper around them, such as the SDL_AudioSystem, the InputManager for SDL input.

* Questionable design choices:

- Singletons. Now, this is an entire debate in its own right, but what happens with the InputManager when you switch scenes? You obviously can't keep processing the inputs from 
a previous scene. At first, I had made all Managers linked to a Scene, but this defeated the point of having a Singleton. So, in the end, everything was kept as a Singleton, and
the InputManager had the hackiest solution possible: The Scene stores inputs, and re-adds them to the InputManager on Scene Enter. This is honestly a bad choice, and I will change it.

- Math Library: I started this Math Library months before Prog 4, and I thought it was almost complete. During Q*bert I realized how wrong I was. I had to basically remake my
TransformComponent, literally every templated Math struct, and in the end there are still some errors in it. For Q*bert, using GLM might've been a better choice, but I'm still proud of it.


All in all, I'm disgusted by my Q*bert code, which was written after the torment of Graphics Programming 2, but I'm mostly proud of my Engine. Q*bert itself is disgusting, because
I was rushed, and didn't quite grasp how much everything is intertwined.