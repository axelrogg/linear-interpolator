package main

import (
	"fmt"
	"math"
	"strconv"
	"strings"
)

func spanishDecimalStringToFloat(decimal string) float64 {
	decimalParts := strings.Split(decimal, ",")
	decimalScale := math.Pow10(len(decimalParts[1]))
	intPart, err := strconv.ParseFloat(decimalParts[0], 64)
	if err != nil {
		panic(err)
	}
	decimalPart, err := strconv.ParseFloat(decimalParts[1], 64)
	if err != nil {
		panic(err)
	}

	return (intPart*decimalScale + decimalPart) / decimalScale

}

func main() {
	fmt.Println("This is a linear interpolator tool.")
	fmt.Println("You may use a comma or a point to specify decimal numbers, but the result will be given using the point convention.")
	fmt.Println("\nUse the following table as a hint:")
	fmt.Println(
		`  Leads  |  Tails
---------+---------
  Lead 1 |  Tail 1
---------+---------
  Lead 2 |  Tail 2 <-- This is your expected result
---------+---------
  Lead 3 |  Tail 3`)
	fmt.Println("\nWhat are your values?")

	var leads [3]string
	var tails [2]string

	fmt.Print("Lead 1: ")
	fmt.Scan(&leads[0])

	fmt.Print("Tail 1: ")
	fmt.Scan(&tails[0])

	fmt.Print("Lead 2: ")
	fmt.Scan(&leads[1])

	fmt.Print("Lead 3: ")
	fmt.Scan(&leads[2])

	fmt.Print("Tail 3: ")
	fmt.Scan(&tails[1])

	var parsedLeads [3]float64
	var parsedTails [2]float64

	for i, val := range leads {
		if strings.Contains(val, ",") {
			parsedLeads[i] = spanishDecimalStringToFloat(val)
		} else {
			parsedVal, err := strconv.ParseFloat(val, 64)
			if err != nil {
				panic(err)
			}
			parsedLeads[i] = parsedVal
		}
	}

	for i, val := range tails {
		if strings.Contains(val, ",") {
			parsedTails[i] = spanishDecimalStringToFloat(val)
		} else {
			parsedVal, err := strconv.ParseFloat(val, 64)
			if err != nil {
				panic(err)
			}
			parsedTails[i] = parsedVal
		}
	}

	// check that all the leads are in increasing or decreasing order and tails follow this order.
	tail2 := parsedTails[0] + (parsedTails[1]-parsedTails[0])*(parsedLeads[1]-parsedLeads[0])/(parsedLeads[2]-parsedLeads[0])
	fmt.Println("Your value is: ", tail2)
}
