#pragma once
#include "sensor.h"
#include "std_lib_facilities.h"
#include "range.h"
#include <set>

set<Beacon> get_beacons(const vector<Sensor>& sensors)
{
    set<Beacon> beacons;
    for(Sensor sensor : sensors)
    {
        beacons.insert(sensor.get_beacon());
    }
    return beacons;
}

vector<Sensor> sensors_crossing_y(int target_y, const vector<Sensor>& sensors)
{
    vector<Sensor> target_sensors;
    for (int i = 0; i < sensors.size(); i++)
    {
        Sensor sensor = sensors[i];
        if(sensor.cross_y(target_y))
        {
            target_sensors.push_back(sensor);
        }
    }
    return target_sensors;
}

pair<int,int> get_min_max_x_of_sensors(const vector<Sensor>& sensors)
{
    Sensor first = sensors[0];
    int min = first.get_left();
    int max = first.get_right();
    for (int i = 1; i < sensors.size(); i++)
    {
        Sensor sensor = sensors[i];
        if(sensor.get_right() > max)  max = sensor.get_right();
        if(sensor.get_left() < min)  min = sensor.get_left();
    }
    return make_pair(min, max);
}

bool is_beacon(int x, int y, const vector<Beacon>& beacons)
{
    for (const Beacon& beacon : beacons)
    {
        if (x == beacon.get_x() && y == beacon.get_y()) return true;
    }

    return false;
}

int count_beacons_at_y(int y, pair<int,int> min_max_x,const set<Beacon>& beacons)
{
    int count = 0;
    for (const Beacon& beacon : beacons)
    {
        if (beacon.get_y() == y && ((min_max_x.first <= beacon.get_x()) && (beacon.get_x() <= min_max_x.second)))
        {
            count++;
        }
    }
    return count;
}

int count_beacons_at_y(int y, Range range,const set<Beacon>& beacons)
{
    int count = 0;
    for (const Beacon& beacon : beacons)
    {
        if (beacon.get_y() == y && ((range.get_left() <= beacon.get_x()) && (beacon.get_x() <= range.get_right())))
        {
            count++;
        }
    }
    return count;
}

int count_scanned_area(vector<Sensor> sensors, int target_y)
{
    vector<Sensor> target_sensors = sensors_crossing_y(target_y, sensors);
    pair<int,int> min_max = get_min_max_x_of_sensors(target_sensors);
    vector<Range> ranges = {Range(min_max.first, min_max.second)};
    set<Beacon> beacons = get_beacons(sensors);
    int beacon_at_range = count_beacons_at_y(target_y,ranges[0], beacons);

    int count = 0;
    for(const Sensor& sensor : target_sensors)
    {
        for (Range range : ranges)
        {
            for(int i = range.get_left(); i <= range.get_right(); i++)
            {
                if (sensor.contains(i, target_y)) count++;
            }
        }
        ranges = subtract_ranges(ranges, sensor.get_range_at_y(target_y));
    }

    return count - beacon_at_range;
};

unsigned long long find_distress_beacon(int search_width, int search_height, vector<Sensor> sensors)
{
    for (int target_y = 0; target_y <= search_height; target_y++)
    {
        vector<Sensor> target_sensors = sensors_crossing_y(target_y, sensors);
        vector<Range> ranges = {Range(0,search_width)};
        for (const Sensor &sensor : target_sensors)
        {
            ranges = subtract_ranges(ranges, sensor.get_range_at_y(target_y));
            /* cout << "ranges size : " << ranges.size() << '\n'; */
            if (ranges.size() == 0)
            {
                /* cout << "y : " << target_y << " searched all\n"; */
                break;
            }
        }
        if (ranges.size() != 0)
        {
            int x = ranges[0].get_left();
            /* cout << "caught at " << x << ',' << target_y << '\n'; */
            cout << "x: " << x << '\n';
            unsigned long long x4 = x * 4;
            cout << "x * 4 : " << x4 << '\n';
            string x4000000 = to_string(x4) + "000000";
            cout << "y: " << target_y << '\n';
            return (unsigned long long)4000000 * (unsigned long long)x + (unsigned long long)target_y;
        }
    }
}