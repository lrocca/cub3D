# cub3D

## Controls

Key | Action
:-: | ------
`W` | Move forward
`S` | Move backward
`A` | Move left
`D` | Move right
`←` | Pan left
`→` | Pan right
`spacebar` | Show minimap
`M` | Toggle music
`ESC` | Exit

You can also use your `mouse` to pan left and right.

## `.cub` file

### Directives

Directive | Arguments | Description
:-------: | --------- | -----------
`R` | `number` width<br>`number` height | Window resolution
`NO` | `string` | Path to north walls texture
`SO` | `string` | Path to south walls texture
`EA` | `string` | Path to east walls texture
`WE` | `string` | Path to west walls texture
`FL` | `string` | Path to floor texture
`CL` | `string` | Path to ceiling texture
`F` | `RGB` | Fallback color for floor
`C` | `RGB` | Fallback color for ceiling
`S` | `string` | Path to main sprite texture
`S3` | `string` | Path to life sprite texture
`S4` | `string` | Path to success sprite texture

- Textures can be provided either in `.png` or `.xpm` format.
- Textures must be above 32×32 dimensions.
- Wall textures must be squared.

### Map

The map must be the last directive of the file.

Character | Description
:-------: | -----------
`0` | Walkable area
`1` | Wall
`2` | Sprite
`3` | Life
`4` | Success
`N` `S` `E` `W` | Player spawn and direction
`space` | Spacer used to create complex maps

- One and only one player spawn must be present in the map.
- All walkable areas (`0`) and sprites (`2`) must be sorrounded by walls (`1`). `space`s are considered areas outside the map and can only be next to walls (`1`).
