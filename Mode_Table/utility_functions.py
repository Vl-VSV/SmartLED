def export_to_csv(table):
    tbl_as_csv = table.get_csv_string().replace('\r', '')
    text_file = open('modes_table.csv', 'w')
    text_file.write(tbl_as_csv)
    text_file.close()


def update_arduino_file(table, file_path='../ColorMusic_WiFi_VSV_Edition/ColorMusic_WiFi_VSV_Edition.ino'):
    with open(file_path, 'r') as file:
        arduino_code = file.read()

    new_comment = f'Режимы:\n{str(table)}\n*/'

    updated_code = arduino_code.split('Режимы:')[0] + new_comment

    with open(file_path, 'w') as file:
        file.write(updated_code)


def update_readme_file(table, file_path='README.md'):
    with open(file_path, 'r') as file:
        md_text = file.read()

    new_table = f'## Все режимы:\n{_to_markdown_table(table)}'

    md_new_text = md_text.split('## Все режимы:')[0] + new_table

    with open(file_path, 'w') as file:
        file.write(md_new_text)


def _to_markdown_table(table):
    markdown = []
    for index, row in enumerate(table.get_string().split('\n')[1:-1]):
        if all(x == '-' or x == '+' for x in row):
            if index > 2:
                markdown.append(row.replace('+', '|').replace('-', ' '))
            else:
                markdown.append(row.replace('+', '|'))
        else:
            markdown.append('|' + row[1:-1] + '|')
    return "\n".join(markdown)
