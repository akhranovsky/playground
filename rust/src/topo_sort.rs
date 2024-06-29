use std::collections::HashSet;

pub type Node = usize;

pub fn topo_sort_kahn(number_of_nodes: usize, edges: Vec<(Node, Node)>) -> Option<Vec<Node>> {
    let mut result = Vec::with_capacity(number_of_nodes);

    if number_of_nodes == 0 {
        return result.into();
    }

    let mut in_degree = vec![0; number_of_nodes];

    for &(_, to) in &edges {
        in_degree[to] += 1;
    }

    let mut queue = Vec::with_capacity(number_of_nodes);
    for i in 0..number_of_nodes {
        if in_degree[i] == 0 {
            queue.push(i);
        }
    }

    while !queue.is_empty() {
        let node = queue.pop().unwrap();
        result.push(node);

        for to in edges
            .iter()
            .filter(|(from, _)| &node == from)
            .map(|&(_, to)| to)
        {
            in_degree[to] -= 1;
            if in_degree[to] == 0 {
                queue.push(to);
            }
        }
    }
    (result.len() == number_of_nodes).then_some(result)
}

#[derive(Debug)]
pub struct CycleDetected(Node, Node);
impl std::fmt::Display for CycleDetected {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "cycle detected: {} <-> {}", self.0, self.1)
    }
}

pub fn topo_sort_dfs(
    number_of_nodes: usize,
    edges: Vec<(Node, Node)>,
) -> Result<Vec<Node>, CycleDetected> {
    let mut result = Vec::with_capacity(number_of_nodes);
    let mut visited = vec![false; number_of_nodes];
    let mut stack = HashSet::with_capacity(number_of_nodes);

    for i in 0..number_of_nodes {
        if !visited[i] {
            stack.insert(i);
            dfs(i, &edges, &mut visited, &mut stack, &mut result)?;
            stack.remove(&i);
        }
    }

    result.reverse();
    Ok(result)
}

fn dfs(
    node: Node,
    edges: &[(Node, Node)],
    visited: &mut [bool],
    stack: &mut HashSet<Node>,
    result: &mut Vec<Node>,
) -> Result<(), CycleDetected> {
    if !visited[node] {
        visited[node] = true;

        for to in edges
            .iter()
            .filter(|(from, _)| &node == from)
            .map(|&(_, to)| to)
        {
            if !stack.insert(to) {
                // If a node is already in the stack, it means that there is a cycle.
                return Err(CycleDetected(node, to));
            }
            dfs(to, edges, visited, stack, result)?;
            stack.remove(&to);
        }
        result.push(node);
    }

    Ok(())
}
