extern crate rand;
use rand::Rng;

use std::collections::HashSet;

mod terrain;

fn main() {
    // Creates empty terrain
    let mut t: [terrain::Cell; terrain::AREA] = [terrain::Cell::Empty; terrain::AREA];
    let mut avail_cells: HashSet<usize> = (0..terrain::AREA).collect();

    // Populates decor
    generate_decor(&mut t, &mut avail_cells);

    // Prints map
    print_terrain_ascii(&t);

    // Computes spawn position (TBI)
    split_field(&mut t, &avail_cells, 10);

    // Prints map
    print_terrain_ascii(&t);
    
    //println!("{:?} ({})", avail_cells, avail_cells.len());

    // Spawns stuff
    place_entities();

    let game_over: bool = true;
    while !game_over {
        do_turn();
    }

    //println!("{:?} ({})", avail_cells, avail_cells.len());
}

fn generate_decor(t: &mut [terrain::Cell; terrain::AREA], avail_cells: &mut HashSet<usize>) {
    // Decor spacing describes the probability of a cell to be a decor
    const DECOR_SPACING: usize = 5;
    // Decor count is deduced from decor spacing and terrain area
    const DECOR_COUNT: usize = terrain::AREA / DECOR_SPACING;
    // Initializes RNG
    let mut rng = rand::thread_rng();

    // Implementation of Algorithm R to choose obstacle locations randomly
    // See : https://en.wikipedia.org/wiki/Reservoir_sampling#Algorithm_R
    let mut reservoir: [usize; DECOR_COUNT] = [0; DECOR_COUNT];
    for kv in avail_cells.iter().enumerate() {        
        if kv.0 < DECOR_COUNT {
            reservoir[kv.0] = *kv.1;
        } else {
            let index = rng.gen_range(0, kv.0 + 1);
            if index < DECOR_COUNT {
                reservoir[index] = *kv.1;
            }
        }
    }

    // Fills the terrain with decor and removes cells from available ones
    for cell in reservoir.iter() {
        t[*cell] = terrain::Cell::Decor;
        avail_cells.remove(cell);
        //NOTE:fbrenot: Might want to create a separate map to list obstacles ?
    }
}

fn split_field(t : &mut[terrain::Cell; terrain::AREA], avail_cells: &HashSet<usize>, split: usize) -> Vec<HashSet<usize>> {
    // To split the terrain, we draw a circle on the terrain and split it in N = split parts
    // Initializes some constants
    const FLOAT_WIDTH:  f64 = terrain::TERRAIN_WIDTH as f64;
    const FLOAT_HEIGHT: f64 = terrain::TERRAIN_HEIGHT as f64;
    const HALF_WIDTH:  f64 = FLOAT_WIDTH  / 2.0;
    const HALF_HEIGHT: f64 = FLOAT_HEIGHT / 2.0;
    
    // Computes the angular region for each split
    let angle_cutoff = 2.0 * std::f64::consts::PI / (split as f64);

    // Computes the minimum radius to be the height or the width of the terrain depending on which is the smallest
    let radius_y = if (2 * terrain::TERRAIN_WIDTH) > terrain::TERRAIN_HEIGHT {
        HALF_HEIGHT
    } else {
        FLOAT_WIDTH
    };

    // Everything on the Y scale is twice as big to make a circle
    let radius_x = radius_y / 2.0;

    // Restricts the iterations on a square that tangents the circle
    let start_x = (HALF_WIDTH  - radius_x).floor() as usize;
    let start_y = (HALF_HEIGHT - radius_y).floor() as usize;

    let end_x = (HALF_WIDTH  + radius_x).floor() as usize;
    let end_y = (HALF_HEIGHT + radius_y).floor() as usize;

    let mut spawn_points = vec![(HashSet::<usize>::new()); split];
    
    // Goes through the map
    for y in start_y..end_y {
        for x in start_x..end_x {

            let pt = terrain::Point{x:x, y:y};
            let cell = terrain::get_cell(&pt);

            // Checks if the current cell is available (we don't want anything to spawn on occupied space)
            if avail_cells.contains(&cell) {
                // Translates the coordinates to the center of the terrain
                let fx = (x as f64) - HALF_WIDTH;
                let fy = (y as f64) - HALF_HEIGHT;

                // Checks if the current cell is inside the circle
                if (fx / radius_x).powi(2) + (fy / radius_y).powi(2) <= 1.0 {
                    // Computes this cell's angle using atan2
                    let angle = (fy / 2.0).atan2(fx) + std::f64::consts::PI;
                    // Computes with split of the board this cell belongs to
                    let part = ((angle / angle_cutoff) as usize) % split;

                    spawn_points[part].insert(cell);
                    
                    if part % 2 == 0 {
                        t[terrain::get_cell(&pt)] = terrain::Cell::Monster;
                    } else {
                        t[terrain::get_cell(&pt)] = terrain::Cell::Obstacle;
                    }
                }
            }
        }
    }
    println!("{:?}", spawn_points);
    spawn_points
}


fn print_terrain_ascii(t: &[terrain::Cell; terrain::AREA]) {
    const BLACK:  char = '◆';
    const WHITE:  char = '◇';
    const SQUARE: char = '◈';
    const DOT:    char = '⟐';
    const SPLIT:  char = '❖';

    // Loop through every cell from top to bottom and left to right
    for y in 0..terrain::TERRAIN_HEIGHT {
        // Store the current position in the map as Point
        let mut pt = terrain::Point {x: 0, y: y};

        if y % 2 == 1 {
            print!("  ");
        }

        for x in 0..terrain::TERRAIN_WIDTH {
            pt.x = x;
            match t[terrain::get_cell(&pt)] {
                terrain::Cell::Empty    => print!("{}   ", WHITE),
                terrain::Cell::Player   => print!("{}   ", SQUARE),
                terrain::Cell::Monster  => print!("{}   ", DOT),
                terrain::Cell::Decor    => print!("{}   ", BLACK),
                terrain::Cell::Obstacle => print!("{}   ", SPLIT),
            }
        }
        println!("");
    }
    println!("");
}

fn place_entities() {

}

fn do_turn() {

}