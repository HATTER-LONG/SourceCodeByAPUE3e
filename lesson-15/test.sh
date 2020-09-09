#!/bin/bash

echo $$

ps -ef | grep "$$"

echo "-------------------------------------"

(pwd;echo $$;ps -ef | grep "$$";)

echo "-------------------------------------"

{
	
pwd; echo $$;ps -ef | grep "$$";
}
