set shiftwidth=4
set tabstop=4

set makeprg=ninja\ -C\ build\ -v
set wildignore+=docs/*,install/*,build/*,test/*,*.o,*.a,*.d,*.gnp,*.cdl

set efm=%f:%l:%c:\ %tarning:\ %m,%f:%l:%c:\ %trror:\ %m,%Dninja:\ Entering\ directory\ `%f',
