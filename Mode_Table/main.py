from prettytable import PrettyTable

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

print("Массив Таймеров:")
timers_table = PrettyTable()
timers_table.align = "l"

timers_table.field_names = ["index", "Режим"]

timers_table.add_row(["0", "Main"])
timers_table.add_row(["1", "Server Requests"])
timers_table.add_row(["2", "Effect_1_3, Effect_2_1, Effect_2_2"])
timers_table.add_row(["3", "Effect_4_*"])
print(timers_table, end="\n")

# Export to csv
tbl_as_csv = modes_table.get_csv_string().replace('\r', '')
text_file = open("modes_table.csv", "w")
text_file.write(tbl_as_csv)
text_file.close()

# Update comment
file_path = "../ColorMusic_WiFi_VSV_Edition/ColorMusic_WiFi_VSV_Edition.ino"  # Относительный путь к файлу
with open(file_path, 'r') as file:
    arduino_code = file.read()

new_comment = f"""Режимы:
{str(modes_table)}
*/

"""

updated_code = arduino_code.split("Режимы:")[0] + new_comment

with open(file_path, 'w') as file:
    file.write(updated_code)