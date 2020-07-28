import sqlite3 from 'sqlite3'
import * as sqlite from 'sqlite'
import { Record } from './interface/Record'

class Database {
  private db?: sqlite.Database

  private addRecordStatement?: sqlite.Statement

  constructor (
    private readonly dbPath: string
  ) { }

  async open (): Promise<void> {
    this.db = await sqlite.open({
      filename: this.dbPath,
      driver: sqlite3.Database
    })

    await this.createTableIfNotExist()
    await this.createPreparedStatements()
  }

  private async createTableIfNotExist (): Promise<void> {
    if (this.db == null) {
      throw new Error('Database not opened')
    }

    await this.db.exec(`create table if not exists record (
      id integer primary key autoincrement,
      created_at integer not null,
      temperature real not null,
      humidity real not null,
      pressure real not null,
      co2 integer not null,
      tvoc integer not null
    );`)
  }

  private async createPreparedStatements (): Promise<void> {
    if (this.db == null) {
      throw new Error('Database not opened')
    }

    this.addRecordStatement = await this.db.prepare(`insert into record (created_at, temperature, humidity, pressure, co2, tvoc) values (
      $created_at,
      $temperature,
      $humidity,
      $pressure,
      $co2,
      $tvoc
    )`)
  }

  async addRecord (createdAt: Date, record: Record): Promise<void> {
    if (this.addRecordStatement == null) {
      throw new Error('Statement not created.')
    }

    const unixTime = Math.floor(createdAt.getTime() / 1000)

    await this.addRecordStatement.run({
      $created_at: unixTime,
      $temperature: record.temperature,
      $humidity: record.humidity,
      $pressure: record.pressure,
      $co2: record.co2,
      $tvoc: record.tvoc
    })
  }
}

export { Database }
