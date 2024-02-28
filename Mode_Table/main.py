from prettytable import PrettyTable
from utility_functions import *

modes_table = PrettyTable()
modes_table.align = "l"

print("Режимы:")
modes_table.field_names = ["№", "Режим", "Скорость", "Яркость", "Цвет"]

modes_table.add_row(["1.1", "Алиса", "", "+", "+"])
modes_table.add_row(["1.2", "Плавная смета цвета", "+", "Насыщенность", ""], divider=True)

modes_table.add_row(["2.1", "Плавная радуга", "+", "Шаг радуги", ""])
modes_table.add_row(["2.2", "Конфетти", "+", "Насыщенность", ""])
modes_table.add_row(["2.3", "Бегающая точка со следами", "+", "Насыщенность", ""])
modes_table.add_row(["2.4", "Огонь", "+", "+", "+"])
modes_table.add_row(["2.5", "Лава", "+", "+", "+"], divider=True)

modes_table.add_row(["3.1", "Многоцветные огоньки из центра", "", "Насыщенность", ""])
modes_table.add_row(["3.2", "Многоцветные огоньки с краю", "", "Насыщенность", ""])
modes_table.add_row(["3.3", "Огоньки из центра", "", "Насыщенность", "+"])
modes_table.add_row(["3.4", "Огоньки с краю", "", "Насыщенность", "+"], divider=True)

modes_table.add_row(["4.1", "Шкала громкости - Градиент", "", "Плавность", ""])
modes_table.add_row(["4.2", "Шкала громкости - Полоски", "", "Плавность", ""])
modes_table.add_row(["4.3", "Шкала громкости - Облака", "", "Плавность", ""])
modes_table.add_row(["4.4", "Шкала громкости - Вечеринка", "", "Плавность", ""])
modes_table.add_row(["4.5", "Шкала громкости - Океан", "+", "Плавность", ""])
modes_table.add_row(["4.6", "Шкала громкости - Радуга", "+", "Плавность", ""])
modes_table.add_row(["4.7", "Шкала громкости - Лава", "+", "Плавность", ""])
modes_table.add_row(["4.8", "Шкала громкости - Лес", "+", "Плавность", ""])
modes_table.add_row(["4.9", "Шкала громкости - Жара", "+", "Плавность", ""])
print(modes_table, end="\n")

# Export to csv
export_to_csv(modes_table)

# Update .ino file
update_arduino_file(modes_table)

# Update README.md file
update_readme_file(modes_table)