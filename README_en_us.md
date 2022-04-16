### pokeglitch

Making some modifications in a Pokémon Red savegame.
At the moment the tool can modify the player name.
To make this change, you need to do the steps below:

```bash
$ cd src/
$ gcc -Wall *.c -o main
```

Now you need to pass your save path to the app:

```bash
$ # if u r using mgba, the cmd below will works
$ main ../rom/pokemon_red.sav
```

If you don't changed the line 25 in the main.c, the new player name is:
`abcdefg`.

### TODO

- [ ] use getopts (unistd.h) to parse command-line params.

- [ ] change player money.

- [ ] ...
