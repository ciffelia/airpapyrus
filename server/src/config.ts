if (process.env.PORT == null) {
  throw new Error('PORT is not set.')
}
export const port = parseInt(process.env.PORT)

if (process.env.ELASTICSEARCH_NODE == null) {
  throw new Error('ELASTICSEARCH_NODE is not set.')
}
export const elasticsearchNode = process.env.ELASTICSEARCH_NODE
