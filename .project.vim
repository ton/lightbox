set shiftwidth=4
set tabstop=4

set makeprg=ninja\ -C\ build\ -v
set wildignore+=docs/*,install/*,build/*,test/*,*.o,*.a,*.d,*.gnp,*.cdl

set efm=%f:%l:%c:\ %tarning:\ %m,%f:%l:%c:\ %trror:\ %m,%f:%l:%c:\ fatal\ %trror:\ %m,%Dninja:\ Entering\ directory\ `%f',/home/ton/development/lightbox/build/.././%f:%l:\ undefined\ reference\ to\ %m
