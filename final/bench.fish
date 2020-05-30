#!/usr/bin/env fish

pushd (dirname (status -f))

function run_code
    set program $argv[1]
    pushd code
    if command test $program.c -nt $program.out
        echo - Compiling $program.c ...
        gcc $program.c -Werror -Wall -Wextra -Wconversion -Wno-unused-result -O3 -o $program.out
        gcc $program.c -Werror -Wall -Wextra -Wconversion -Wno-unused-result -O3 -D TIMER -o $program.timer.out
        if test $status -ne 0
            exit
        end
    end
    popd
    echo - Running $program ...
    if test ! -e out/$program
        mkdir out/$program
    end
    true > bench/$program.txt

    echo Measuring total time ...
    for i in (seq 1 10)
        set filename (printf "bcspwr%02d.txt" $i)
        time -a -o bench/$program.txt code/$program.out <in/$filename >out/$program/$filename
        diff out/$program/$filename out/ans/$filename
        if test $status -ne 0
            echo "answer is not correct";
            exit
        end
    end
    true > bench/$program.detail.txt;
    echo Measuring detailed time ...
    for i in (seq 1 10)
        set filename (printf "bcspwr%02d.txt" $i)
        eval ./code/$program.timer.out <in/$filename >/dev/null 2>>bench/$program.detail.txt
    end

    echo Measuring Memory usage ...
    if test ! -e bench/$program.memory
        mkdir bench/$program.memory
    end
    for i in (seq 1 10)
        set filename (printf "bcspwr%02d.txt" $i)
        valgrind 2>>/dev/null --tool=massif  --massif-out-file=bench/$program.memory/$i.txt code/$program.out  < in/$filename >/dev/null
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
