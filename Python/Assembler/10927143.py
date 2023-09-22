
table1 = [
    "add", "addf", "addr", "and", 
    "clear", "comp", "compf", "compr",
    "div", "divf", "divr", 
    "fix", "float",
    "hio",
    "j", "jeq", "jgt", "jlt", "jsub",
    "lda", "ldb", "ldch", "ldf", "ldl", "lds", "ldt", "ldx", "lps",
    "mul", "mulf", "mulr",
    "norm",
    "or",
    "rd", "rmo", "rsub",
    "shiftl", "shiftr", "sio", "ssk", "sta", "stb", "stch", "stf", "sti",
    "stl", "sts", "stsw", "stt", "stx", "sub", "subf", "subr", "svc",
    "td", "tio", "tix", "tixr",
    "wd" 
]

table2 = [ "START", "END", "BYTE", "WORD", "RESB", "RESW", "EQU", "BASE", "LTORG"]
table3 = [ "A", "X", "L", "B", "S", "T", "F", "PC", "SW" ]
table4 = [ ",", "+", "-", "*", "/", ":", ";", "?", "'", ".", "=", "#", "@" ]

SIC_opcode_table = {
    'ADD': '18', 'AND': '40', 'COMP': '28', 'DIV': '24', 'J': '3C',
    'JEQ': '30', 'JGT': '34', 'JLT': '38', 'JSUB': '48', 'LDA': '00',
    'LDCH': '50', 'LDL': '08', 'LDX': '04', 'MUL': '20', 'OR': '44',
    'RD': 'D8', 'RSUB': '4C', 'STA': '0C', 'STCH': '54', 'STL': '14',
    'STX': '10', 'SUB': '1C', 'TD': 'E0', 'TIX': '2C', 'WD': 'DC'
}

SICXE_opcode_table = {
    'ADD': '18', 'ADDF': '58', 'ADDR': '90', 'AND': '40', 'CLEAR': 'B4',
    'COMP': '28', 'COMPF': '88', 'COMPR': 'A0', 'DIV': '24', 'DIVF': '64',
    'DIVR': '9C', 'FIX': 'C4', 'FLOAT': 'C0', 'HIO': 'F4', 'J': '3C',
    'JEQ': '30', 'JGT': '34', 'JLT': '38', 'JSUB': '48', 'LDA': '00',
    'LDB': '68', 'LDCH': '50', 'LDF': '70', 'LDL': '08', 'LDS': '6C',
    'LDT': '74', 'LDX': '04', 'LPS': 'D0', 'MUL': '20', 'MULF': '60',
    'MULR': '98', 'NORM': 'C8', 'OR': '44', 'RD': 'D8', 'RMO': 'AC',
    'RSUB': '4C', 'SHIFTL': 'A4', 'SHIFTR': 'A8', 'SIO': 'F0',
    'SSK': 'EC', 'STA': '0C', 'STB': '78', 'STCH': '54', 'STF': '80',
    'STI': 'D4', 'STL': '14', 'STS': '7C', 'STSW': 'E8', 'STT': '84',
    'STX': '10', 'SUB': '1C', 'SUBF': '5C', 'SUBR': '94', 'SVC': 'B0',
    'TD': 'E0', 'TIO': 'F8', 'TIX': '2C', 'TIXR': 'B8', 'WD': 'DC'
}

class Assembler:
    def __init__(self):
        self.LC = 0
        self.symbol_table = {}
        self.table5 = [None]*100
        self.table6 = [None]*100
        self.table7 = [None]*100

    def add_to_hash_table(self, table, item):
        index = hash(item) % 100
        while table.get(index) is not None:
            index = (index + 1) % 100
        table[index] = item

    def parse_line(self, line):
        # 跳過註解行
        if line.startswith('.'):
            return
        # 假設每行由label、opcode和operand組成，並且它們由空格分隔
        parts = line.split()
        if len(parts) == 3:
            label, opcode, operand = parts
        elif len(parts) == 2:
            label, opcode = parts
            operand = None
        elif len(parts) == 1:
            opcode = parts[0]
            label = operand = None
        else:
            return
        
        if label:
            # 如果有標籤，則將其添加到符號表中
            self.add_to_hash_table(self.symbol_table, (label, self.LC))

        # 處理操作碼
        if opcode in SIC_opcode_table or opcode in SICXE_opcode_table:
            # 如果操作碼需要LC增加，則增加相應的值
            # 這裡需要根據你的具體需求來決定如何增加LC
            self.LC += 3 # 一般SIC指令的長度為3，但你可能需要根據實際情況進行調整
        elif opcode in ['WORD']:
            self.LC += 3
        elif opcode in ['RESW']:
            self.LC += 3 * int(operand)
        elif opcode in ['RESB']:
            self.LC += int(operand)
        elif opcode in ['BYTE']:
            # 處理字節常數
            if operand.startswith('C'):
                # 字符常量
                self.LC += len(operand) - 3  # -3 是因為需要扣除C' 和 '兩個字符
            elif operand.startswith('X'):
                # 十六進制常量
                self.LC += (len(operand) - 3) // 2  # 每兩個十六進制數字佔一個字節
        elif opcode in ['END']:
            # 處理結束行
            pass
    

if __name__ == "__main__":
    filename = input("請輸入檔名：")

    # 開啟檔案
    try:
        with open(filename, 'r') as file:
            # 讀取每一行並儲存到一個列表中
            lines = file.readlines()

            # 移除每一行的換行符並切分
            lines = [line.strip() for line in lines]

        # 印出切分後的資料
        for line in lines:
            print(line)

    except FileNotFoundError:
        print("檔案不存在，請確認檔名是否正確。")

    
    # Create an instance of the assembler
    assembler = Assembler()

    # Iterate over the lines in the input file and process each one
    for line in lines:
        assembler.parse_line(line)
        
    # Printing the Symbol Table
    print("Symbol Table: ", assembler.symbol_table)