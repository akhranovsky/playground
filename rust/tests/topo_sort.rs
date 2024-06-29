#[cfg(test)]
mod kahn {
    use rust_lib::topo_sort::topo_sort_kahn;

    #[test]
    fn empty_graph() {
        assert_eq!(topo_sort_kahn(0, vec![]), vec![].into());
    }
    #[test]
    fn no_edges() {
        assert_eq!(topo_sort_kahn(3, vec![]), vec![2, 1, 0].into());
    }
    #[test]
    fn all_connected_directly() {
        assert_eq!(
            topo_sort_kahn(3, vec![(0, 1), (1, 2)]),
            vec![0, 1, 2].into()
        );
    }
    #[test]
    fn all_connected_reversed() {
        assert_eq!(
            topo_sort_kahn(3, vec![(2, 1), (1, 0)]),
            vec![2, 1, 0].into()
        );
    }
    #[test]
    fn two_targets() {
        assert_eq!(
            topo_sort_kahn(3, vec![(0, 1), (0, 2)]),
            vec![0, 2, 1].into()
        );
    }
    #[test]
    fn two_sources() {
        assert_eq!(
            topo_sort_kahn(3, vec![(1, 0), (2, 0)]),
            vec![2, 1, 0].into()
        );
    }
    #[test]
    fn wiki() {
        assert_eq!(
            topo_sort_kahn(
                12,
                vec![
                    (3, 8),
                    (3, 10),
                    (5, 11),
                    (7, 11),
                    (7, 8),
                    (8, 9),
                    (11, 10),
                    (11, 9),
                    (11, 2)
                ]
            ),
            vec![7, 6, 5, 11, 2, 4, 3, 10, 8, 9, 1, 0].into()
        );
    }
    #[test]
    fn full_cycle() {
        assert_eq!(
            topo_sort_kahn(5, vec![(0, 1), (1, 2), (2, 3), (3, 4), (4, 0)]),
            None
        );
    }

    #[test]
    fn part_cycle() {
        assert_eq!(
            topo_sort_kahn(5, vec![(0, 1), (1, 2), (2, 3), (3, 2)]),
            None
        );
    }

    #[test]
    fn self_cycle() {
        assert_eq!(topo_sort_kahn(3, vec![(0, 1), (1, 2), (2, 2)]), None);
    }
}

#[cfg(test)]
mod dfs {
    use rust_lib::topo_sort::topo_sort_dfs;

    #[test]
    fn empty_graph() {
        assert_eq!(topo_sort_dfs(0, vec![]).unwrap(), vec![]);
    }
    #[test]
    fn no_edges() {
        assert_eq!(topo_sort_dfs(3, vec![]).unwrap(), vec![2, 1, 0]);
    }
    #[test]
    fn all_connected_directly() {
        assert_eq!(
            topo_sort_dfs(3, vec![(0, 1), (1, 2)]).unwrap(),
            vec![0, 1, 2]
        );
    }
    #[test]
    fn all_connected_reversed() {
        assert_eq!(
            topo_sort_dfs(3, vec![(2, 1), (1, 0)]).unwrap(),
            vec![2, 1, 0]
        );
    }
    #[test]
    fn two_targets() {
        assert_eq!(
            topo_sort_dfs(3, vec![(0, 1), (0, 2)]).unwrap(),
            vec![0, 2, 1]
        );
    }
    #[test]
    fn two_sources() {
        assert_eq!(
            topo_sort_dfs(3, vec![(1, 0), (2, 0)]).unwrap(),
            vec![2, 1, 0]
        );
    }
    #[test]
    fn wiki() {
        assert_eq!(
            topo_sort_dfs(
                12,
                vec![
                    (3, 8),
                    (3, 10),
                    (5, 11),
                    (7, 11),
                    (7, 8),
                    (8, 9),
                    (11, 10),
                    (11, 9),
                    (11, 2)
                ]
            )
            .unwrap(),
            vec![7, 6, 5, 11, 4, 3, 10, 8, 9, 2, 1, 0]
        );
    }
    #[test]
    fn full_cycle() {
        assert!(topo_sort_dfs(5, vec![(0, 1), (1, 2), (2, 3), (3, 4), (4, 0)]).is_err());
    }

    #[test]
    fn part_cycle() {
        assert!(topo_sort_dfs(5, vec![(0, 1), (1, 2), (2, 3), (3, 2)]).is_err());
    }

    #[test]
    fn self_cycle() {
        assert!(topo_sort_dfs(3, vec![(0, 1), (1, 2), (2, 2)]).is_err());
    }
}
