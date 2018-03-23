<?php

interface iStorage
{

    public function save(iProduct $product);

    public function load(int $id);

    public function edit(int $id, array $newValues);

    public function delete(int $id);

    public function getAll();
}