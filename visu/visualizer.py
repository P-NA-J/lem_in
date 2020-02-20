import networkx as nx
import plotly.graph_objects as go
from chart_studio.plotly import plot, iplot
import sys

G = nx.Graph()

anthills = []
for line in sys.stdin:
    anthills.append(line)

nb_ants = anthills.pop(0)

node_names = {}

i = 0
err = 0
flag = 0
label = []
name = []
for elem in anthills:
    s = ""
    s = s.join(elem)
    if '#' in elem:
        if "start" in elem:
            flag = 1
        elif "end" in elem:
            flag = 2
        err += 1
        continue
    elif '-' in elem:
        break
    if flag == 1:
        start_node = str(s.split(' ')[0])
        G.add_node(i, name=start_node, pos=[0, 2])
        node_names[start_node] = i
        label.append('START')
    elif flag == 2:
        end_node = str(s.split(' ')[0])
        G.add_node(i, name=end_node, pos=[1, 0])
        node_names[end_node] = i
        label.append('END')
    else:
        n_name = s.split(' ')[0]
        G.add_node(i, name=n_name)
        node_names[n_name] = i
        label.append('')
    flag = 0
    i += 1

i += err
del anthills[:i]

"""
Function to add annotations
"""
def make_annotations(pos, anno_text, font_size=14, font_color='rgb(10,10,10)'):
    L= len(pos)
    if len(anno_text) != L:
        raise ValueError('The lists pos and text must have the same len')
    annotations = []
    for k in range(L):
        annotations.append(dict(text=anno_text[k], 
                                x=pos[k][0], 
                                y=pos[k][1]+0.075,#this additional value is chosen by trial and error
                                xref='x1', yref='y1',
                                font=dict(color= font_color, size=font_size),
                                showarrow=False))
    return annotations  

"""
Adding edges to the Graph object
"""
edges = []
for elem in anthills[:i]:
    if (elem.find('-') == -1):
        break
    edges = elem.split('-')
    n1_name = edges[0]
    n2_name = edges[1].replace('\n','')
    G.add_edge(node_names[n1_name], node_names[n2_name])

"""
Setting up nodes positions
"""
pos=nx.fruchterman_reingold_layout(G)
nx.set_node_attributes(G, pos, 'pos') 

edge_trace = go.Scatter(
    x=[],
    y=[],
    line=dict(width=0.5,color='#888'),
    hoverinfo='none',
    mode='lines')

for edge in G.edges():
    x0, y0 = G.node[edge[0]]['pos']
    x1, y1 = G.node[edge[1]]['pos']
    edge_trace['x'] += tuple([x0, x1, None])
    edge_trace['y'] += tuple([y0, y1, None])

node_trace = go.Scatter(
    x=[],
    y=[],
    text=[],
    mode='markers',
    hoverinfo='text',
    marker=dict(
        showscale=True,
        colorscale='YlGnBu',
        reversescale=True,
        color=[],
        size=30,
        colorbar=dict(
            thickness=15,
            title='Node Connections',
            xanchor='left',
            titleside='right'
        ),
        line=dict(width=2)))

for node in G.nodes():
    x, y = G.node[node]['pos']
    node_trace['x'] += tuple([x])
    node_trace['y'] += tuple([y])

n_name_attributes = nx.get_node_attributes(G, 'name') 
n_kind_attributes = nx.get_node_attributes(G, 'kind')

for node, adjacencies in enumerate(G.adjacency()):
    node_trace['marker']['color']+=tuple([len(adjacencies[1])])
    node_info = '\n# of connections: '+str(len(adjacencies[1]))
    node_trace['text']+=tuple([node_info])

"""
Setting up Plotly go.Figure object from Networkx Graph
"""
fig = go.Figure(data=[edge_trace, node_trace],
             layout=go.Layout(
                title='<br>Lem_in graph made with Python',
                titlefont=dict(size=16),
                showlegend=False,
                hovermode='closest',
                margin=dict(b=20,l=5,r=5,t=40),
                annotations=[dict(
                    text="LEM_IN BY PAULO AND ALBANO",
                    showarrow=False,
                    xref="paper", yref="paper",
                    x=0.5, y="auto")],
                xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
                yaxis=dict(showgrid=False, zeroline=False, showticklabels=False)))

fig['layout'].update(annotations=make_annotations(pos, label))
fig.show()

## parse ants paths
