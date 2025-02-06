def run(edges):
    n = 1000

    adj = [set() for _ in range(n)]
    for a, b in edges:
        adj[a].add(b)
        adj[b].add(a)

    signatures = [None] * n
    for v in range(n):
        deg = len(adj[v])
        neigh_degs = sorted(len(adj[u]) for u in adj[v])
        signatures[v] = (deg, tuple(neigh_degs))
    
    vertices_sorted = sorted(range(n), key=lambda v: signatures[v])
    S = sorted(vertices_sorted[:31])
    
    marker_edges = set()
    center = S[0]
    for v in S[1:]:
        if center < v:
            marker_edges.add( (center, v) )
        else:
            marker_edges.add( (v, center) )
    
    def edge_exists(u, v):
        return v in adj[u] or u in adj[v]

    marker_present = all(edge_exists(u, v) for (u, v) in marker_edges)

    if marker_present:
        return []
    else:
        new_edges = []
        for (u, v) in marker_edges:
            if not edge_exists(u, v):
                new_edges.append([u, v])
        return new_edges
