import networkx as nx
import plotly.graph_objects as go
from chart_studio.plotly import plot, iplot
import random
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
        G.add_node(i, name=start_node, kind="START", pos=[0, 2])
        node_names[start_node] = i
    elif flag == 2:
        end_node = str(s.split(' ')[0])
        G.add_node(i, name=end_node, kind="END", pos=[1, 0])
        node_names[end_node] = i
    else:
        n_name = s.split(' ')[0]
        G.add_node(i, name=n_name, kind="")
        node_names[n_name] = i
    flag = 0
    i += 1

init_pos = nx.get_node_attributes(G, 'pos')

i += err
del anthills[:i]

edges = []
for elem in anthills[:i]:
    if (elem.find('-') == -1):
        break
    edges = elem.split('-')
    n1_name = edges[0]
    n2_name = edges[1].replace('\n','')
    G.add_edge(node_names[n1_name], node_names[n2_name])

#isolates = list(nx.isolates(G))
#G.remove_nodes_from(isolates)
#print(isolates)

is_planar = nx.check_planarity(G)
print(is_planar)
pos=nx.spring_layout(G, seed = 100)
#for edge in G.edges():
nx.set_node_attributes(G, pos, 'pos') 

#dmin=1
#ncenter=0
#for n in pos:
#    x,y=pos[n]
#    d=(x-0.5)**2+(y-0.5)**2
#    if d<dmin:
#        ncenter=n
#        dmin=d
#
#p=nx.single_source_shortest_path_length(G,ncenter)

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

## right sided color gradient bar
node_trace = go.Scatter(
    x=[],
    y=[],
    text=[],
    mode='markers',
    hoverinfo='text',
    marker=dict(
        showscale=True,
        # colorscale options
        #'Greys' | 'YlGnBu' | 'Greens' | 'YlOrRd' | 'Bluered' | 'RdBu' |
        #'Reds' | 'Blues' | 'Picnic' | 'Rainbow' | 'Portland' | 'Jet' |
        #'Hot' | 'Blackbody' | 'Earth' | 'Electric' | 'Viridis' |
        colorscale='YlGnBu',
        reversescale=True,
        color=[],
        size=10,
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

#print(G.nodes)
n_name_attributes = nx.get_node_attributes(G, 'name') 
n_kind_attributes = nx.get_node_attributes(G, 'kind')

for node, adjacencies in enumerate(G.adjacency()):
    node_trace['marker']['color']+=tuple([len(adjacencies[1])])
    node_info = 'Node kind: ' + n_kind_attributes[node] + '\n# of connections: '+str(len(adjacencies[1]))
    node_trace['text']+=tuple([node_info])

fig = go.Figure(data=[edge_trace, node_trace],
             layout=go.Layout(
                title='<br>Network graph made with Python',
                titlefont=dict(size=16),
                showlegend=False,
                hovermode='closest',
                margin=dict(b=20,l=5,r=5,t=40),
                annotations=[ dict(
                    text="Python code: <a href='https://plot.ly/ipython-notebooks/network-graphs/'> https://plot.ly/ipython-notebooks/network-graphs/</a>",
                    showarrow=False,
                    xref="paper", yref="paper",
                    x=0.5, y="auto"),
                    dict(text="putting a point", x=0.5, y=0.5),
                    dict(text="putting a sec point", x=0.2, y=0.55)],
                xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
                yaxis=dict(showgrid=False, zeroline=False, showticklabels=False)))


fig.show()


## parse ants paths


print (G.node)
print (G.number_of_nodes())

print (list(G.edges))
print (G.number_of_edges())
print (nb_ants)
