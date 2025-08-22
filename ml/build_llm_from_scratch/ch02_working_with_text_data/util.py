def text_corpus() -> str:
    with open('The_Verdict.txt', 'r', encoding='utf-8') as txt_file:
        return txt_file.read()