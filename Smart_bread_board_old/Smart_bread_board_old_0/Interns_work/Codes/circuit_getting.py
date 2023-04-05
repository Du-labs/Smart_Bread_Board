import SchemDraw as schem
import SchemDraw.elements as e
d = schem.Drawing()
#d.add(e.RES, label='10K$\Omega$')
d.add(e.CAP, d='down', botlabel='0.2$\mu$F')
d.draw()
d.save('schematic.eps')