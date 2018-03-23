<?php

class SimpleFileStorage implements iStorage
{
    public function __construct($path)
    {
        $this->path = 'C:\Users\Qna\Desktop\stdi\PHP\Ex4\Products\\';
    }

    public function save(iProduct $product)
    {
        $id   = $product->getId();
        $path = $this->path . $id;

        if (file_exists($path))
        {
            throw new Exception("File exist!");
        }

        $serialized = serialize($product);

        file_put_contents($path, $serialized);
    }

    public function load(int $id)
    : iProduct
    {
        $path = $this->path . $id;

        if (!file_exists($path))
        {
            throw new Exception("File does not exist!");
        }

        $content = file_get_contents($path);

        return unserialize($content);
    }

    public function edit(int $id, array $newValues)
    {
        try
        {
            $product = $this->load($id);
            $product->editProduct($newValues);
            $this->delete($id);
            $this->save($product);
        }catch (Exception $e)
        {
            throw new Exception("Can't edit file!");
        }
    }

    public function delete(int $id)
    {
        $path = $this->path . $id;

        if (!file_exists($path))
        {
            throw new Exception("File does not exist!");
        }

        unlink($path);
    }

    public function getAll()
    {
        $files = array_diff(scandir($this->path), array('..', '.'));

        $products = [];

        foreach ($files as $file)
        {
            $content = file_get_contents($this->path . $file);
            $content = unserialize($content);

            $products[$content->getId()] = $content->getName();
        }

        return $products;
    }


}