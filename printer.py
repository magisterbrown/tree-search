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

class TreePrinter(gdb.ValuePrinter):
    def __init__(self, state):
        self.state = state
        self.val = state["state_value"]
        self.n_children = 5

    def to_string(self):
        if(self.state["parrent"] == 0):
            par = "null"
        else:
            par = self.state["parrent"].dereference()["state_value"]
        childs=list()
        for i in range(self.n_children):
            if self.state["children"][i]==0:
                childs.append( "null")
            else:
                childs.append(float(self.state["children"][i].referenced_value()["state_value"]))
        
        return "\n Parrent: {} <- Value: {} Children: {}".format(par, self.val, childs)



def build_pretty_printer():
    pp = gdb.printing.RegexpCollectionPrettyPrinter(
        "microfield")
    pp.add_printer('LField', '^LField$', FieldPrinter)
    pp.add_printer('tree', '^TreeNode$', TreePrinter)
    return pp

import gdb.printing
gdb.printing.register_pretty_printer(
    gdb.current_objfile(),
    build_pretty_printer())

