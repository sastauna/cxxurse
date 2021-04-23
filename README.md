# cxxurse

<img src="misc/icon.png" width="168px"/>

*It's pronounced "curses" because you carry the "x" to the end."

Files have a naming convention sorta.

suffix|meaning
------|-------
`0`   |template
`1`   |constexpr
`2`   |runtime

Since there are no constexpr loops, the most efficient algorithm might not be
constexpr, unfortunately. Templates are just for fooling around to get better.
