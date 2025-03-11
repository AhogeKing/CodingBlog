package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"path/filepath"
	"strings"
)

var keysOrder []string

type dictionary map[string][2]string

var validPOS = []string{"n", "v", "adj", "adv", "pron", "conj"}

func isValidPOS(POS string) bool {
	for _, str := range validPOS {
		if str == POS {
			return true
		}
	}
	return false
}

func wait() {
	fmt.Print("\nPress 'Enter' to continue...")
	bufio.NewReader(os.Stdin).ReadBytes('\n')
}

// Load dictionary from file. Returns map[string][2]string and error.
func loadDict(filePath string) (dictionary, error) {
	dictionary := make(map[string][2]string)
	lineIndex := 0
	keysOrder = nil // Clear global order

	file, err := os.Open(filePath)
	if err != nil {
		if os.IsNotExist(err) {
			fmt.Printf("File does not exist, returning an empty dictionary: %s\n", filePath)
			return dictionary, nil
		}
		return nil, err
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		lineIndex++

		// Skip empty lines
		if line == "" {
			continue
		}

		// Get the first indices of space and period
		whiteIndex := strings.IndexRune(line, ' ')
		pIndex := strings.IndexRune(line, '.')

		if whiteIndex == -1 || pIndex == -1 {
			return nil, fmt.Errorf("format error in line %d: %q", lineIndex, line)
		}

		spelling := line[:whiteIndex]
		POS := strings.TrimSpace(line[whiteIndex:pIndex])
		if !isValidPOS(POS) {
			return nil, fmt.Errorf("invalid POS in line %d", lineIndex)
		}
		translation := strings.TrimSpace(line[pIndex+1:])

		dictionary[spelling] = [2]string{POS, translation}
		keysOrder = append(keysOrder, spelling)
	}

	if err := scanner.Err(); err != nil {
		return nil, fmt.Errorf("error reading file: %v", err)
	}
	return dictionary, err
}

// Print dictionary. If flag is true, print in order; otherwise, print unordered.
func printDict(dict dictionary, flag bool) {
	if len(dict) == 0 {
		fmt.Println("The dictionary is empty.")
		wait()
		return
	}

	if flag {
		for _, key := range keysOrder {
			fmt.Printf("%-20s %s. %s\n", key, dict[key][0], dict[key][1])
		}
	} else {
		for key, value := range dict {
			fmt.Printf("%-20s %s. %s\n", key, value[0], value[1])
		}
	}
	wait()
}

// Add a word to the dictionary.
func addWord(dict dictionary) error {
	fmt.Print("Enter the word in English: ")
	reader := bufio.NewReader(os.Stdin)
	spelling, err := reader.ReadString('\n')
	if err != nil {
		return fmt.Errorf("failed to read the word: %v", err)
	}
	spelling = strings.TrimSpace(spelling)

	// Check for duplicate
	if _, exists := dict[spelling]; exists {
		fmt.Printf("The word '%s' already exists. Overwrite? (y/n): ", spelling)
		confirmation, _ := reader.ReadString('\n')
		if strings.TrimSpace(confirmation) != "y" {
			fmt.Println("Word not overwritten.")
			return nil
		}
	}

	fmt.Print("Enter the part of speech (n v adj adv pron conj): ")
	POS, err := reader.ReadString('\n')
	if err != nil {
		return fmt.Errorf("failed to read the part of speech: %v", err)
	}
	POS = strings.TrimSpace(POS)
	if !isValidPOS(POS) {
		return fmt.Errorf("invalid part of speech: %s", POS)
	}

	fmt.Print("Enter the translation, separated by ',' or ';': ")
	translation, err := reader.ReadString('\n')
	if err != nil {
		return fmt.Errorf("failed to read the translation: %v", err)
	}
	translation = strings.TrimSpace(translation)
	if translation == "" {
		return fmt.Errorf("translation cannot be empty")
	}

	dict[spelling] = [2]string{POS, translation}
	keysOrder = append(keysOrder, spelling)
	fmt.Printf("The word '%s' has been successfully added to the dictionary.\n", spelling)
	wait()
	return nil
}

func deletekWord(dict dictionary, word string) {
	if _, exist := dict[word]; exist {
		delete(dict, word)
		for i, key := range keysOrder {
			if key == word {
				keysOrder = append(keysOrder[:i], keysOrder[i+1:]...)
				break
			}
		}
		fmt.Printf("The word '%s' has been deleted from the dictionary.\n", word)
	} else {
		fmt.Printf("the word '%s' does not exist in the dictionary.\n", word)
	}
	wait()
}

func searchWord(dict dictionary, word string) {
	if value, exist := dict[word]; exist {
		fmt.Printf("find it!\n%-4s. %s", value[0], value[1])
	} else {
		fmt.Printf("couldn't find word '%s' in the dictionary.\n", word)
	}
	wait()
}

func saveToFile(dict dictionary, filePath string) error {
	file, err := os.Create(filePath)
	if err != nil {
		return fmt.Errorf("failed to create or open file: %v", err)
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	for _, key := range keysOrder {
		value := dict[key]
		line := fmt.Sprintf("%s %s.%s\n", key, value[0], value[1])
		_, err := writer.WriteString(line)
		if err != nil {
			return fmt.Errorf("failed to write to file: %v", err)
		}
	}

	// 确保所有内容写入磁盘
	if err := writer.Flush(); err != nil {
		return fmt.Errorf("failed to flush buffer: %v", err)
	}
	return nil
}

func main() {
	workingDir, err := os.Getwd()
	if err != nil {
		fmt.Println("Error getting current directory:", err)
		return
	}
	filePath := filepath.Join(workingDir, "test.txt")
	fmt.Println("File path:", filePath)

	dict, err := loadDict(filePath)
	if err != nil {
		log.Fatal(err)
	}
	isChanged := false

	for {
		fmt.Println("--------------------")
		fmt.Println(" (1) Print dictionary\n",
			"(2) Search word\n",
			"(3) Add word\n",
			"(4) Delete word\n",
			"(0) Exit")
		fmt.Println("--------------------")
		reader := bufio.NewReader(os.Stdin)
		choice, _ := reader.ReadString('\n')
		choice = strings.TrimSpace(choice)

		switch choice {
		case "1":
			printDict(dict, true)
		case "2":
			fmt.Print("Enter word to search: ")
			word, _ := reader.ReadString('\n')
			word = strings.TrimSpace(word)
			searchWord(dict, word)
		case "3":
			err := addWord(dict)
			if err != nil {
				fmt.Println("Error adding word:", err)
			}
			isChanged = true
		case "4":
			fmt.Println("Enter word to delete:")
			word, _ := reader.ReadString('\n')
			word = strings.TrimSpace(word)
			deletekWord(dict, word)
			isChanged = true
		case "0":
			if isChanged {
				fmt.Print("Save changes to the dictionary? (y/n): ")
				confirmation, _ := reader.ReadString('\n')
				if strings.TrimSpace(confirmation) == "y" {
					err := saveToFile(dict, filePath)
					if err != nil {
						fmt.Println("Error saving dictionary:", err)
					} else {
						fmt.Println("Dictionary saved successfully.")
					}
				}
			}
			fmt.Println("Goodbye!")
			return
		default:
			fmt.Println("Invalid choice, please try again.\n")
		}
		fmt.Println()
	}
}
