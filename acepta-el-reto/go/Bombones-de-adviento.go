package main

import (
	"fmt"
	"strconv"
)

func main() {
	var numero string
	var numero1 int
	var numero2 int
	var maximo int

	for {
		_, err := fmt.Scan(&numero)
		if numero == "" || err != nil {
			break
		}
		if numero == "0" && maximo != 0 {
			fmt.Printf("%d\n", maximo)
			numero2 = 0
			maximo = 0
			continue
		}
		numero1 = numero2
		numero2, err = strconv.Atoi(numero)
		if err != nil {
			continue
		}
		if numero1+numero2 > maximo {
			maximo = numero1 + numero2
		}
	}
}
