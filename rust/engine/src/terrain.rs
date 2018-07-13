pub const TERRAIN_WIDTH: usize = 20;
pub const TERRAIN_HEIGHT: usize = 2 * TERRAIN_WIDTH;

#[derive(Copy, Clone, Debug)]
pub enum Cell {
    Empty,
    Player,
    Monster,
    Decor,
    Obstacle,
}

pub struct Point {
    pub x: usize,
    pub y: usize,
}

pub struct Terrain {
    width: usize,
    height: usize,
    cells: [Cell; TERRAIN_WIDTH],
}

pub const AREA: usize = TERRAIN_WIDTH * TERRAIN_HEIGHT;

pub fn is_valid_cell(cell: usize) -> bool {
    cell < AREA
}

pub fn is_valid_point(pt: &Point) -> bool {
    pt.x < TERRAIN_WIDTH && pt.y < TERRAIN_HEIGHT
}

pub fn get_x(cell: usize) -> usize {
    cell % TERRAIN_WIDTH
}

pub fn get_y(cell: usize) -> usize {
    cell / TERRAIN_WIDTH
}

pub fn get_point(cell: usize) -> Point {
    Point{x: get_x(cell), y: get_y(cell)}
}

pub fn get_cell(pt: &Point) -> usize {
    pt.x + pt.y * TERRAIN_WIDTH
}



pub enum EntityType {
    Player,
    Monster,
}

pub struct Entity {
    id: usize,
    name: usize,
    position: Point,
    kind: EntityType,
}
