#!/usr/bin/env fish

pushd (dirname (status -f))

function run_code
    set program $argv[1]
    pushd code
    if command test $program.c -nt $program.out
        echo - Compiling $program.c ...
        gcc $program.c -Wno-unused-result -O3 -o $program.out
    end
    popd
    echo - Running $program ...
    if test ! -e out/$program
        mkdir out/$program
    end
    true > bench/$program.txt
    for i in (seq 1 10)
        set filename (printf "bcspwr%02d.txt" $i)
        time code/$program.out <in/$filename >out/$program/$filename 2>> bench/$program.txt
        diff out/$program/$filename out/ans/$filename
    end
end

if test (count $argv) -eq 1
    run_code $argv
else
    for program_path in code/*.c
        set program (string split -r -m1 . (basename $program_path))[1]
        run_code $program
    end
end

popd
