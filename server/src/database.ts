import { Client } from '@elastic/elasticsearch'
import { Record } from './interface/Record'

class Database {
  private readonly client: Client

  constructor (elasticsearchNode: string) {
    this.client = new Client({ node: elasticsearchNode })
  }

  async open (): Promise<void> {
    await this.client.ping()

    await this.createIndexIfNotExist()
  }

  private async createIndexIfNotExist (): Promise<void> {
    const { body: indexExists } = await this.client.indices.exists({ index: 'airpapyrus' })
    if (indexExists) {
      return
    }

    await this.client.indices.create({
      index: 'airpapyrus',
      body: indexTemplate
    })
  }

  async addRecord (createdAt: Date, record: Record): Promise<void> {
    await this.client.index({
      index: 'airpapyrus',
      body: {
        created_at: createdAt.getTime() / 1000,
        ...record
      }
    })
  }
}

const indexTemplate = {
  mappings: {
    dynamic: 'strict',
    properties: {
      created_at: {
        type: 'date',
        format: 'epoch_second'
      },
      temperature: {
        type: 'float'
      },
      humidity: {
        type: 'float'
      },
      pressure: {
        type: 'float'
      },
      co2: {
        type: 'integer'
      },
      tvoc: {
        type: 'integer'
      }
    }
  }
} as const

export { Database }
