*This project has been created as part of the 42 curriculum by lchamard and yben-dje.*

# Ghibli Shell
## Description
You like **Ghibli**? You like **Bash**? If this is the case for you (I hope), this project is made for you! This project is a partial remake of bash bringing Ghibli magic to your terminal ✨.

## Roadmap
- [X] Execute built-ins before searching the binaries in the PATH
- [ ] Fix the io FDs in exec pipexline
- [ ] Fix waitpid in exec pipexline
- [ ] Add a command history file
- [ ] Handle the mallocs in the parser (and everywhere) 😅

### Module names (Warning spoil)
We gived the name of Ghibli's characters to the project's modules.

| Module                | Name                    | Why?                                                          |
|-----------------------|-------------------------|---------------------------------------------------------------|
| TTY                   | Arietty                 | Her name contains "TTY".                                      |
| Tokeniser             | Shizuku                 | She is a raw stone waiting to be polished.                    |
| Parser                | Haru                    | The story is the polished stone.                              |
| Executor              | Miyasaki                | He is the movie director.                                     |
| Expander              | Ponyo                   | She reconciles and merge the humans' world and the sea.       |
| Error manager         | Ursula                  | She's an artist.                                              |
| Built-in              | Sheeta                  | The levitation stone is magic like the built-in commands.     |
| File runner           | Jiro                    | He creates planes.                                            |
| Env variable manager  | Totoro                  | Because he cares about the Environment.                       |

Open a discussion thread if you want more info about the choices.

## Instructions
### Build
To build the project, you can run this command
```bash
make
```
Recompile the project with
```bash
make re
```

If you don't want the animations or you want the debug compiler flag, run this command
```bash
DEBUG=please make
```
Recompile the project with
```bash
DEBUG=please make re
```

### Execute
To execute Ghiblishell, run
```bash
./minishell
```
You can also run scripts from a file (usualy .gsh files).
```bash
./minishell my_script.gsh
```
This will execute the file line by line until minishell encounters an error or reach the end of the file.
Exit the shell with the `exit` command.

### Additional features
- You can edit the environment variables such as the `PROMPT` variable in the `~/.ghiblirc` gsh file.
- The prompt is displayed using the `PROMPT` environment variable. You can modify the variable to change the prompt.
- The shell supports `source`.
- The built-in echo supports escapes.
- Simply executing `export` will display the list of all variables.
- The `SHLVL` est supporté.

## Resources
We mainly used the man of the commands for documentation. The ascii arts animations are made by *yben-dje*.

The Little Totoro dot art is from [emojicombos.com](https://emojicombos.com/totoro-dot-art).

The catbus dot arts was made by *yben-dje* using a mix of image processing, automated tools and manual drawing. The frames are directly based of the film.

What? You just said I-I ? Oh no, "AI"? I don't know what that means. Well... ok... I do know what "AI" is. BUT DO YOU KNOW WHO YOU'RE TALKING TO? GET OUT OF THERE! WE DO NOT USE IA HERE! **USING AI IS A SKILL ISSUE AND WE ARE GIGA CHADS. SO STOP TALKING TO US ABOUT AI!**

Hum... How are you today 🤗?

Go watch **Ghibli** films now!
