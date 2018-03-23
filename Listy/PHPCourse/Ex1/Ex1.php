<?php

function printNumberAndSpaces($number)
{
    echo $number;

    $spaces = 10 - floor(log10($number));
    echo str_repeat(" ", $spaces);
}

function printRow($i, $word, $len)
{
    $spaces    = ceil($len / 2) - $i;
    $endSpaces = $len - $spaces;

    $num = $len - 2 * $spaces;
    printNumberAndSpaces($num);

    foreach (range(1, $len) as $number)
    {
        if ($number <= $spaces || $number > $endSpaces)
        {
            echo " ";
        } else
        {
            echo $word[$number - 1];
        }
    }
    echo "\n";
}

foreach ($argv as $i => $word)
{
    if ($i != 0)
    {
        $charArr = preg_split('//u', $word, -1, PREG_SPLIT_NO_EMPTY);
        $len     = sizeof($charArr);

        for ($i = 1; $i <= ceil($len / 2); $i++)
        {
            printRow($i, $charArr, $len);
        }
        for ($i = ceil($len / 2) - 1; $i > 0; $i--)
        {
            printRow($i, $charArr, $len);
        }

        echo PHP_EOL;
    }
}
