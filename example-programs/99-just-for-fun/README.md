# Just for Fun!

I need a break from writing tutorials, so I'm doing fun programs to amuse me. I'll try to heavily comment these so anyone curious can see what I was thinking.

## [compare-render-options-01.ino](compare-render-options-01.ino)

I'm not precisely sure what the difference is between using `pushImage()` and `drawSprite()`, but I wanted to know which one was faster, so I whipped up a UI to see the difference. `pushImage()` is faster, at least in the way I used it in this program.

## [hello-tone-repeater.ino](hello-tone-repeater.ino)

Do you want to know what repeating beep of one note sounds like with different intervals? That's what this does =P Making it was also a good opportunity to refine the `Button` class I've been building out since I started learning the BB_SPI_LCD library.

## [hello-tone-two-tones.ino](hello-tone-two-tones.ino)

A sketch that lets you hear two alternating tones with variable durations and gaps. If the gap is set to 0, then not all frequency pairs will play properly and I'm not sure why. This one is a little bit more interesting just because it has more tonal variation. 

## [spinning-triangle.ino](spinning-triangle.ino)

It's a triangle that spins! I wanted to build something that had triangles so I did. Drawing triangles is kind of slow.