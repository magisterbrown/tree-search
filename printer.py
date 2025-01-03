import gdb
import gdb.printing
class FieldPrinter(gdb.ValuePrinter):
    def __init__(self, val):
        self._val = val

    def to_string(self):
        height = int(self._val["height"])
        width = int(self._val["width"]) 
        field = str()
        for i in range(height):
            field += "\n"
            for j in range(width):
                fig = str(self._val["board"][i*width+j])
                if(fig == "NO_PIECE"):
                    fig = "O"
                #field += " 0"
                field += " "+fig

        return "\n Width: {} Height: {} {}".format(self._val["width"], self._val["height"], field)

    def display_hint(self):
        return 'hint'

def str_lookup_function(val):
    print("LOOOK")
    return None


def build_pretty_printer():
    pp = gdb.printing.RegexpCollectionPrettyPrinter(
        "microfield")
    pp.add_printer('LField', '^LField$', FieldPrinter)
    return pp

import gdb.printing
gdb.printing.register_pretty_printer(
    gdb.current_objfile(),
    build_pretty_printer())

