<?php

class Graph
{
    private $color;
    private $belongs;
    private $graph;

    public function __construct($color, $belongs, $graph)
    {
        $this->color = $color;
        arsort($this->color);
        $this->belongs = $belongs;
        $this->graph   = $graph;
    }

    public function isEmpty()
    {
        if ($this->graph == [])
        {
            return true;
        } else
        {
            return false;
        }
    }

    public function maxColor()
    {
        return reset($this->color);
    }

    public function allNodes()
    {
        $nodes = [];
        foreach ($this->graph as $key => $list)
        {
            array_push($nodes, $key);
        }

        return $nodes;
    }

    public function maxColorNodes()
    {
        $nodes = [];
        $max   = $this->maxColor();
        foreach ($this->color as $key => $color)
        {
            if ($color != $max)
            {
                break;
            }
            array_push($nodes, $key);
        }

        return $nodes;
    }

    public function deleteNodes($nodes)
    {
        $newColor   = [];
        $newBelongs = [0 => [], 1 => []];
        $newGraph   = [];

        foreach ($this->color as $key => $color)
        {
            if (!in_array($key, $nodes))
            {
                $newColor[$key] = $color;
            }
        }

        foreach ($this->belongs[0] as $node)
        {
            if (!in_array($node, $nodes))
            {
                array_push($newBelongs[0], $node);
            }
        }

        foreach ($this->belongs[1] as $node)
        {
            if (!in_array($node, $nodes))
            {
                array_push($newBelongs[1], $node);
            }
        }

        foreach ($this->graph as $key => $list)
        {
            if (!in_array($key, $nodes))
            {
                $newGraph[$key] = [];
                foreach ($list as $node)
                {
                    if (!in_array($node, $nodes))
                    {
                        array_push($newGraph[$key], $node);
                    }
                }
            }
        }

        return new Graph($newColor, $newBelongs, $newGraph);
    }

    public function attractor($nodes, $player)
    {
        $changed   = true;
        $lastNodes = $nodes;

        while ($changed)
        {
            $playerNodes = [];

            foreach ($this->belongs[$player] as $node)
            {
                foreach ($this->graph[$node] as $neighbor)
                {
                    if (in_array($neighbor, $lastNodes))
                    {
                        array_push($playerNodes, (int)$node);
                        break;
                    }
                }
            }

            $otherPlayerNodes = [];

            foreach ($this->belongs[1 - $player] as $node)
            {
                $forall = true;

                foreach ($this->graph[$node] as $neighbor)
                {
                    if (!in_array($neighbor, $lastNodes))
                    {
                        $forall = false;
                        break;
                    }
                }

                if ($forall == true)
                {
                    array_push($otherPlayerNodes, (int)$node);
                }
            }

            $newNodes = array_unique(array_merge($lastNodes, $playerNodes, $otherPlayerNodes));

            if ($newNodes === $lastNodes)
            {
                $changed = false;
            }

            $lastNodes = $newNodes;
        }

        return $newNodes;
    }

}

function solve(Graph $g)
{
    if ($g->isEmpty())
    {
        return [0 => [], 1 => []];
    }

    $p = $g->maxColor();

    $u        = $g->maxColorNodes();
    $i        = $p % 2;
    $j        = 1 - $i;
    $a        = $g->attractor($u, $i);
    $returned = solve($g->deleteNodes($a));

    if ($returned[$j] == [])
    {
        return [$i => array_unique(array_merge($a, $returned[$i])), $j => []];
    }

    $b         = $g->attractor($returned[$j], $j);
    $returned2 = solve($g->deleteNodes($b));

    return [$i => $returned2[$i], $j => array_unique(array_merge($returned2[$j], $b))];

}

function readInput()
{
    $line    = readline();
    $line    = explode(" ", $line);
    $n0      = $line[0];
    $n1      = $line[1];
    $m       = $line[2];
    $graph   = [];
    $color   = [];
    $belongs = [0 => [], 1 => []];

    for ($i = 0; $i < $n0 + $n1; $i++)
    {
        $player          = $i < $n0 ? 0 : 1;
        $line            = readline();
        $line            = explode(" ", $line);
        $graph[$line[0]] = [];
        $color[$line[0]] = $line[1];
        array_push($belongs[$player], $line[0]);
    }

    for ($i = 0; $i < $m; $i++)
    {
        $line = readline();
        $line = explode(" ", $line);
        array_push($graph[$line[0]], $line[1]);
    }

    $line = readline();

    return [new Graph($color, $belongs, $graph), $line];
}


$input = readInput();
$graph = $input[0];
$init  = $input[1];

$solved = solve($graph);

if (in_array($init, $solved[0]))
{
    echo "0" . PHP_EOL;
} else
{
    echo "1" . PHP_EOL;
}